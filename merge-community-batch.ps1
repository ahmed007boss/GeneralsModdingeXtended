# merge-community-batch.ps1
# Stages the next batch of community/main changes onto main WITHOUT committing.
# Review and test the staged changes, then commit manually with:
#   git commit -m "Apply community batch N"
# Main branch always wins conflicts (-X ours).
#
# Usage:
#   .\merge-community-batch.ps1              # stage next 40 commits
#   .\merge-community-batch.ps1 -BatchSize 20
#   .\merge-community-batch.ps1 -Status      # show progress only
#   .\merge-community-batch.ps1 -Abort       # abort a stopped cherry-pick

param(
    [int]$BatchSize = 40,
    [switch]$Status,
    [switch]$Abort
)

$RepoRoot     = $PSScriptRoot
$CommitFile   = Join-Path $RepoRoot ".git\community_commits.txt"
$ProgressFile = Join-Path $RepoRoot ".git\community_merge_progress.txt"

if ($Abort) {
    git cherry-pick --abort
    Write-Host "Cherry-pick aborted. Staged changes cleared." -ForegroundColor Yellow
    exit 0
}

# Read full commit list (hash only)
$AllCommits = (Get-Content $CommitFile) | ForEach-Object { ($_ -split ' ')[0] }
$Total = $AllCommits.Count

# Read progress
$Done = 0
if (Test-Path $ProgressFile) {
    $Done = [int](Get-Content $ProgressFile)
}

$Remaining = $Total - $Done
$Pct = if ($Total -gt 0) { [math]::Round(($Done / $Total) * 100, 1) } else { 0 }

Write-Host ""
Write-Host "Community merge progress: $Done / $Total commits staged+committed ($Pct%)" -ForegroundColor Cyan
Write-Host "Remaining: $Remaining commits" -ForegroundColor Cyan

if ($Status) { exit 0 }

if ($Done -ge $Total) {
    Write-Host "All $Total commits have been applied. Nothing left to do!" -ForegroundColor Green
    exit 0
}

# Warn if there are already staged changes (previous batch not yet committed)
$stagedCount = (git diff --cached --name-only 2>$null | Measure-Object -Line).Lines
if ($stagedCount -gt 0) {
    Write-Host ""
    Write-Host "WARNING: You have $stagedCount staged files not yet committed." -ForegroundColor Red
    Write-Host "Commit the current batch first: git commit -m `"Apply community batch`"" -ForegroundColor Yellow
    Write-Host "Then re-run this script for the next batch." -ForegroundColor Yellow
    exit 1
}

# Determine this batch
$BatchEnd   = [math]::Min($Done + $BatchSize, $Total)
$Batch      = $AllCommits[$Done..($BatchEnd - 1)]
$BatchCount = $Batch.Count

Write-Host ""
Write-Host "Staging batch: commits $($Done + 1) - $BatchEnd (batch size: $BatchCount)" -ForegroundColor Yellow
Write-Host "First: $($AllCommits[$Done])"
Write-Host "Last:  $($AllCommits[$BatchEnd - 1])"
Write-Host ""

# Cherry-pick without committing; -X ours means main wins all conflicts
$result = git cherry-pick --no-commit -X ours @Batch 2>&1
$exitCode = $LASTEXITCODE

if ($exitCode -ne 0) {
    Write-Host ""
    Write-Host "Cherry-pick stopped mid-batch (unresolvable conflict or error):" -ForegroundColor Red
    Write-Host $result
    Write-Host ""
    Write-Host "Options:" -ForegroundColor Yellow
    Write-Host "  Resolve conflicts manually, then: git cherry-pick --continue"
    Write-Host "  Skip the problematic commit:      git cherry-pick --skip"
    Write-Host "  Abort and discard this batch:     .\merge-community-batch.ps1 -Abort"
    Write-Host ""
    Write-Host "Progress NOT updated until you commit and re-run." -ForegroundColor Yellow
    exit 1
}

# Update progress now that staging succeeded
$BatchEnd | Set-Content $ProgressFile

$staged = (git diff --cached --name-only 2>$null | Measure-Object -Line).Lines
Write-Host "Staged $staged files from $BatchCount commits." -ForegroundColor Green
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Cyan
Write-Host "  1. Review:  git diff --cached --stat"
Write-Host "  2. Test your build"
Write-Host "  3. Commit:  git commit -m `"chore: apply community batch ($($Done+1)-$BatchEnd / $Total)`""
Write-Host "  4. Run .\merge-community-batch.ps1 again for the next batch"
