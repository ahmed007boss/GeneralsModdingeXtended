## GMX Documentation Authoring Guide (Prompt/Instructions)

**CRITICAL: READ THIS ENTIRE GUIDE COMPLETELY BEFORE CREATING OR EDITING ANY DOCUMENTATION FILE**

**MANDATORY**: This instruction file must be read in its entirety from start to finish before creating or editing any documentation file. Do NOT skip any sections. Do NOT ignore any rules or requirements. Every section contains critical information that must be followed. Missing even a single requirement can result in incorrect, incomplete, or inconsistent documentation that will require rework and delays the review process.

**CRITICAL POLICY - DO NOT SKIP ANYTHING**: Every required section, link, version flag, Retail document, cross-reference, inline property example, and Source Files link must be completed for each doc. If a property references another documented entity (e.g., Science, Upgrade, Object), link it in the Type field (e.g., “see Science documentation”) and provide a minimal inline Example line. Always create/update the Retail document if the feature exists in Retail.

**⚠️ CRITICAL REMINDER - RETAIL DOCUMENTATION (DO NOT SKIP):** After completing the GMX documentation, you MUST create or update the Retail documentation file if the feature exists in Retail versions. This is a MANDATORY step that must be completed for every documentation update. See step 5 in "Mandatory Research Workflow" and the "Retail Documentation Files (Mandatory)" section below. **DO NOT SUBMIT OR COMPLETE DOCUMENTATION WITHOUT CREATING/UPDATING THE RETAIL DOCUMENT IF RETAIL FEATURES EXIST.**

This guide defines the exact process and format for creating or updating documentation in `Docs/`, optimized for modders. It standardizes structure, review flow, version marking, cross-references, examples, and templates, following the current best sample (`ObjectBehaviorsModules/AutoHealBehavior.md`) and expanding it with strict versioning and research requirements.

### Scope and Goals
- Provide modder-facing docs for INI-configurable content with zero executable code; only references/links and INI examples are allowed.
- Cover three doc families:
  - Global config (one block per game): `AIData`, `GameData`, `multiplayer`.
  - Entry lists (many entries modder-defined): e.g., `Science`, `ParticleSystem`, `Weapon`.
  - Modules/behaviors/components added inside `Object` entries: e.g., `AutoHealBehavior`, `CashBountyPower`, `FireWeaponCollide`, Upgrade/Update modules, Draw/Body components, etc.
- Ensure accuracy by studying the code and its dependencies thoroughly before edits.

### Global Rule: Avoid Technical Code Terminology
**CRITICAL**: Write documentation in modder-friendly language. Avoid technical code terms, implementation details, internal function names, or programming concepts that modders won't understand.

**What to avoid**:
- Internal function names (e.g., `GetComponent`, `parseComponent`, `buildFieldParse`)
- Internal status codes or enum values not exposed to modders (e.g., `COMPONENT_STATUS_NONE`, `OBJECT_STATUS_CAN_STEALTH`)
- Implementation details (e.g., "returns NULL", "early return", "lookup method")
- Programming concepts (e.g., "singleton", "polymorphism", "virtual function")
- Internal data structures (e.g., "std::vector", "map", "iterator")

**What IS allowed**:
- References to source files (`.h` and `.cpp` files) in the Source Files section — these help modders who want to check the actual code
- Base class references in Source Files — these help developers understand inheritance
- INI property names exactly as they appear in parse tables — these are what modders use
- Enum string values as they appear in INI files (e.g., "NORMAL", "PRISTINE") — these are what modders type

**Rewrite approach**: When describing behavior, focus on what happens from a modder's perspective. Instead of "GetComponent lookups will only find the first match", write "systems that look up components by name will only find the first matching component, causing unpredictable behavior where the wrong component may be targeted." Instead of "returns COMPONENT_STATUS_NONE", write "does not function and cannot be damaged, healed, or accessed by any systems." Instead of mentioning implementation details like "lazy loading" or "resolved lazily", link to the actual entity/type that the property references (e.g., if a property references an Animation2d template, say "References an animation template defined in [Animation2d](../Animation2d.md) configuration" and link the type in the Type field).

### Mandatory Research Workflow (Before Writing)

**CRITICAL**: Before creating or editing any documentation, you MUST thoroughly study the class across ALL 4 versions in this exact order: GMX Zero Hour → Retail Zero Hour 1.04 → GMX Generals → Retail Generals 1.04. Do NOT skip any version. Do NOT assume availability. This includes verifying actual property names from parse tables, not guessing or assuming based on outdated documentation.

**CRITICAL PROCESS COMPLIANCE**: Follow this workflow EXACTLY as instructed. Do NOT miss any step. Do NOT skip version checks. Do NOT assume availability without checking all 4 versions.

1. Identify the class/feature to document and collect source locations (GMX-first):
   - GMX (primary): `GeneralsMD/Code/GameEngine/Include/` and `GeneralsMD/Code/GameEngine/Source/` (and `Generals/` equivalents when relevant).
   - Retail code (Retail Zero Hour 1.04 and Retail Generals 1.04): `E:\Games\Command and Conquer - Generals - Work\Generals Source\CnC_Generals_Zero_Hour\GeneralsMD` and `...\Generals` (header/source), plus their INI folders.

2. Read both header and source files of the target class and any directly used dependencies across ALL versions. Track:
   - **Parse tables** (`buildFieldParse` or `FieldParse` arrays) in source `.cpp` files - these define the EXACT property names as they appear in INI files. Verify property names match what you document.
   - Member variables linked via `offsetof(Class, member)` in parse tables - these show which member each property fills.
   - Constructor defaults - read constructor implementation to get actual default values, not guesses.
   - Enums and corresponding name arrays (string tables), keeping order consistent.
   - Base classes and module interfaces (UpdateModule, SpecialPowerModule, CollideModule, UpgradeMux, DamageModuleInterface, etc.).
   - For each property, identify the exact parser function used (e.g., `INI::parseReal`, `INI::parseDurationUnsignedInt`, `INI::parseIndexList`, or custom like `ObjectPrerequisite::parseObjectPrerequisites`). Note implications (units, normalization, validation).
   - **CRITICAL - Base class documentation check**: If the class has a base class that has documentation (e.g., `Component.md` is the base for `ElectronicsComponent.md`), you MUST read and review the base class documentation to ensure consistency. Inherited properties, enum values, descriptions, limitations, conditions, and dependencies must match exactly between base and derived documentation. This ensures modders get consistent information regardless of which documentation they read.
  - **CRITICAL - Parent/Child parsing pattern recognition**: When examining parse tables, look for entries that use custom parser functions (not standard `INI::parse*` functions). These often indicate parent/child relationships. Common patterns:
    - **Pattern 1 - Nested blocks**: Parent parse table has entry like `{ "ChildName", ChildClass::parseChildClass, NULL, 0 }` where `parseChildClass` is a static function that creates and parses child entities. The child name in the parse table matches the INI block name.
    - **Pattern 2 - Container storage**: The custom parser function typically creates a new instance, parses its properties, and adds it to a container (vector, list, etc.) in the parent. Look for `new ChildClass()`, `initFromINIMulti()`, and `parent->addChild()` or `parent->m_children.push_back()` patterns.
    - **Pattern 3 - Multiple instances**: If multiple child blocks of the same type can exist, they're stored in a container. If only one child block can exist, it's stored as a single member variable.
    - **Documentation implications**: 
      - Child entities should have their own separate documentation files.
      - Parent documentation should reference child entities with links to their documentation.
      - Parent documentation should NOT duplicate all child properties - only mention that children can be added and link to child documentation.
      - Use clear terminology that describes the parent/child relationship (e.g., "child entities are nested within parent entities").

3. Version comparison (MANDATORY):
   - **CRITICAL**: You MUST check all 4 versions in this exact order: GMX Zero Hour → Retail Zero Hour 1.04 → GMX Generals → Retail Generals 1.04. Do NOT skip any version. Do NOT assume availability based on GMX alone.
   - **CRITICAL**: Compare parse tables, headers, and enum definitions across ALL 4 versions. Record availability per version/game for every property, enum value, and entity.
   - **CRITICAL**: Check if the feature exists in Generals/Code path (GMX Generals) vs GeneralsMD/Code path (GMX Zero Hour). If a Components/ directory doesn't exist in Generals/, it's Zero Hour only. If it exists in both, it's in both GMX variants.
   - Compare GMX vs Retail (Retail Zero Hour 1.04 / Retail Generals 1.04) parse tables and headers for additions/removals/changed semantics.
   - Compare Generals vs Zero Hour variants in both GMX and Retail when applicable.
   - **Verify property names** - ensure the property names in your documentation exactly match those in the parse tables (e.g., `JammingDamageCap` not `EWDamageCap`, `CanBeJammedByDirectJammers` not `CanBeJammedDirect`).

4. Examples research (GMX-first):
   - GMX examples: `e:\Games\Command and Conquer - Generals - Work\Patches\WW2030\INI\...`
   - Retail examples: `e:\Games\Command and Conquer - Generals - Work\Generals Source\Sources\Generals\...\INI\...` (Retail Generals 1.04) and `e:\Games\Command and Conquer - Generals - Work\Generals Source\Sources\Zero Hour\...\INI\...` (Retail Zero Hour 1.04)
   - Remove all comment lines in example snippets.
   - Use real examples that demonstrate actual property usage in the codebase.

5. **⚠️ Create/Update Retail Documentation (MANDATORY - DO NOT SKIP THIS STEP)**:
   - **CRITICAL**: After creating/updating the GMX documentation, you MUST check if the feature exists in Retail versions (Retail Generals 1.04 or Retail Zero Hour 1.04).
   - **MANDATORY ACTION**: If Retail features exist, you MUST create or update a Retail documentation file in the Retail codebase path at `E:\Games\Command and Conquer - Generals - Work\Generals Source\CnC_Generals_Zero_Hour\ModdingDocs\...` (or equivalent path for Retail Generals). **THIS IS NOT OPTIONAL. THIS STEP MUST BE COMPLETED.**
   - **Retail document rules** (see detailed section below):
     - Include ONLY Retail features (remove all GMX-only content).
     - Use Retail version flags only (e.g., `*(v1.04)*`, `*(v1.04, Zero Hour only)*`).
     - Use Retail examples only (from `Sources/Zero Hour` or `Sources/Generals` paths).
     - Follow the same document structure, but exclude GMX-only sections entirely.
   - **If GMX-only feature**: Do NOT create Retail documents (e.g., `Component.md` is GMX Zero Hour only, so no Retail document).
   - **⚠️ THIS STEP IS MANDATORY - DO NOT SKIP IT. DO NOT COMPLETE DOCUMENTATION WITHOUT CREATING/UPDATING THE RETAIL DOCUMENT IF RETAIL FEATURES EXIST. EVERY RETAIL FEATURE MUST HAVE A CORRESPONDING RETAIL DOCUMENT.**

### File Placement and Naming
- Create or edit the relevant doc file under `Docs/` (or subfolder) matching the feature area:
  - Global configs at `Docs/AIData.md`, `Docs/GameData.md`, `Docs/multiplayer.md`.
  - Entities at `Docs/Science.md`, `Docs/ParticleSystem.md`, `Docs/Weapon.md`, etc.
  - Modules under `Docs/ObjectBehaviorsModules/`, `Docs/ObjectModules/`, `Docs/ModuleBase/`, etc.

### ⚠️ Retail Documentation Files (MANDATORY - DO NOT SKIP)

**🚨 CRITICAL - THIS IS A MANDATORY STEP THAT MUST BE COMPLETED FOR EVERY DOCUMENTATION UPDATE**

This is a MANDATORY step in the documentation workflow (see step 5 in "Mandatory Research Workflow"). For features that exist in Retail versions (Retail Generals 1.04 or Retail Zero Hour 1.04), you MUST create or update a Retail documentation file in the Retail codebase path. **THIS IS NOT OPTIONAL. DO NOT SKIP THIS STEP.**

**When to create Retail documents**:
- **After creating/updating GMX documentation**: Once the GMX documentation is complete, check if any of the documented features exist in Retail versions.
- **If Retail features exist**: Create or update the Retail document.
- **If GMX-only feature**: Do NOT create Retail documents (e.g., `Component.md` is GMX Zero Hour only, so no Retail document).

**Retail document location**: `E:\Games\Command and Conquer - Generals - Work\Generals Source\CnC_Generals_Zero_Hour\ModdingDocs\...` (or equivalent path for Retail Generals)

**Retail document rules**:
- **GMX-only features**: Do NOT create Retail documents (e.g., `Component.md` is GMX Zero Hour only, so no Retail document).
- **Retail features**: Create/edit the Retail document with ONLY Retail features (no GMX-only content).
- **Remove GMX-only sections**: Remove all GMX-only properties, enums, conditions, limitations, examples, and notes from the mirror.
- **Keep Retail features only**: Include only properties, enums, and features that exist in Retail Zero Hour 1.04 or Retail Generals 1.04.
- **Version flags in mirror**: Use Retail version flags only (e.g., `*(v1.04)*`, `*(v1.04, Zero Hour only)*`). Do not mention GMX in mirror files.
- **Examples in mirror**: Use Retail examples only (from `Sources/Zero Hour` or `Sources/Generals` paths), remove GMX examples.
- **Structure**: Follow the exact same document structure and rules as the GMX document (same sections, linking, examples, version flags), but exclude GMX-only properties/sections entirely.
 - **Parity with GMX (CRITICAL)**: For functionality that exists in both GMX and Retail, mirror the depth and clarity of the GMX doc in the Retail doc. Copy and adapt shared Usage bullets (Limitations/Conditions/Dependencies), Notes, and Template inline comments to ensure equivalent coverage. Do not leave the Retail doc with shorter or poorer descriptions for shared functionality.

**Example**: For `ActiveBody.md`:
- **GMX version** (`Docs/ObjectModules/ActiveBody.md`): Includes all GMX features (jamming damage GMX Zero Hour only, components GMX Zero Hour only, etc.) plus Retail features (MaxHealth, InitialHealth, subdual damage).
- **Retail mirror** (`E:\Games\Command and Conquer - Generals - Work\Generals Source\CnC_Generals_Zero_Hour\ModdingDocs\ObjectBody\ActiveBody.md`): Includes ONLY Retail features (MaxHealth, InitialHealth, subdual damage for Zero Hour only). No jamming damage, no components, no GMX-only content.

**🚨 CRITICAL - THIS STEP MUST BE COMPLETED FOR EVERY DOCUMENTATION UPDATE. DO NOT SKIP CREATING/UPDATING RETAIL MIRROR FILES WHEN RETAIL FEATURES ARE PRESENT. THIS IS A MANDATORY REQUIREMENT, NOT AN OPTIONAL STEP.**

### Full TODO Flow (CRITICAL & MANDATORY)
Before you create or edit ANY documentation file, you MUST generate this full TODO list and follow it step-by-step. Do NOT wait for review to begin; execute the list immediately. When you are asked to “follow the instruction,” you MUST generate and use this Full TODO Flow without deviation. Each item references sections in this guide for details.

0) Identify all code files across the four versions (CRITICAL)
- Locate header/source files for the target in: GMX Zero Hour, Retail Zero Hour 1.04, GMX Generals, Retail Generals 1.04
- Record exact relative paths (headers, sources, factories/registration points)
- If a version is not present, explicitly note "not present" and proceed

1) Identify scope and availability (see “Versioning Rules” and “Overview”)
- Confirm entity/module name and placement path in Docs
- Check availability across ALL 4 versions (GMX ZH → Retail ZH 1.04 → GMX Gens → Retail Gens 1.04)
- Decide: GMX-only, Retail-only, or mixed; note GMX-only styling rules (Title/Section coloring)

2) Collect source references (see “Source Files” and “Version Comparison”)
- Find headers and sources for GMX (GeneralsMD and Generals if applicable)
- Find Retail headers/sources if feature exists in Retail
- Note base class(es) for Source Files (list base first)

3) Deep code study (MANDATORY) (see “Mandatory Research Workflow”, “Property Parsing and Validation”, “Cross-Usage Research”)
- Read headers and sources end-to-end for the target across ALL 4 versions in this exact order: GMX Zero Hour → Retail Zero Hour 1.04 → GMX Generals → Retail Generals 1.04
- Inspect parse tables (`FieldParse`/`buildFieldParse`), custom parsers, and child-block parsers
- Verify member defaults from constructors/member initializers
- Find and read all getters/setters and call sites that consume parsed members (UI, gameplay, AI)
- Check error/validation paths (asserts, throws, clamps) and document user-facing effects
- Enumerate enums and corresponding name arrays; confirm order and full value set (GMX-first)
- Note base classes and interfaces that affect INI behavior

4) Extract parse surface (see “Property Format” and “Enum Format”)
- Copy property names from parse tables exactly
- Map `offsetof`/members; record defaults from constructors
- Identify enums and string arrays; collect all values (GMX-first)
 - Identify child/parent nested parsers and document as separate child entities where required

5) Draft document skeleton (see “Required Document Structure”)
- Title + Status; Overview with availability line
- Table of Contents with internal anchors
- Properties categories; per-property blocks using Property Format
- Enum Value Lists with values and flags
- Examples; Usage (Limitations/Conditions/Dependencies)
- Template with inline comments for EVERY property line
- Notes; Modder Scenarios (placeholder); Source Files; Changes History; Document Log; Status/Reviewers

6) Link pass (internal/external) (see “Internal Linking — Mandatory” and “Cross-References (Mandatory)”) 
- Add internal links for every in-doc property/enum mention
- Add external links for referenced entities (Object, Upgrade, Science, Weapon, FXList, etc.)
- Add per-property “invalid reference” notes where names are referenced (Object/Science/Upgrade/KindOf/Item)
 - Ensure links are OUTSIDE backticks and anchors exist where linked

7) Retail document gate (see “Retail Documentation Files (MANDATORY)”) 
- If feature exists in Retail: create/update Retail doc with ONLY Retail content and flags
- Remove all GMX-only content from Retail doc; adjust examples/template
- Keep structure identical to GMX doc sans GMX-only content; update version flags and examples to Retail

8) Version flags and styling (see “Versioning Rules” and “Title/Section Headings and Availability”)
- Add version lines to all properties/sections/enums
- Apply GMX-only blue heading styling: title for GMX-only docs; section headings for mixed docs

9) Final validation (CRITICAL — verify against ALL rules in this guide)
- Availability lines present and correct in Overview and each property/enum/category
- Version flags applied everywhere required (sections, properties, enums, enum values) with correct formats
- GMX-only styling rules followed (title colored for GMX-only docs; GMX-only sections colored in mixed docs)
- Retail document created/updated when Retail features exist; Retail doc contains ONLY Retail content
 - Retail↔GMX parity achieved for all shared functionality (Usage, Notes, Template comments match in depth)
- Internal property linking applied in ALL sections (outside code blocks); anchors exist and work
- External links for referenced entities (Object, Upgrade, Science, Weapon, FXList, etc.) use correct relative paths
- Per-property inline Example line exists in Properties; no examples duplicated outside unless required by section
- Template includes concise inline comments for EVERY property line
- Invalid-reference behavior included in property descriptions where names are referenced (Object/Science/Upgrade/KindOf/Item)
- Enum sections list ALL values (GMX-first) with individual version flags; source/array references noted
- Usage section includes Limitations, Conditions, Dependencies with correct content (no duplication)
- Examples compile as INI; no comment lines inside fenced blocks; demonstrate OR/AND semantics where relevant
- Source Files: base class listed first; all file links are clickable; GMX/Retail paths accurate
- Changes History covers feature/code changes only; Document Log covers documentation edits only
- Status block updated (Documentation Status, Last Updated, Certification); Reviewers section has open slots
- Cross-Usage checklist scanned; discovered interactions reflected in Usage
- Spot-check link integrity (property anchors and relative paths)

10) Status and reviewers (see “Review and Certification Workflow”) 
- Set Status block; add/update Last Updated
- Leave at least two reviewer slots

11) Retail-specific TODO (execute now)
 - Set target Retail doc path under `CnC_Generals_Zero_Hour/Docs/...` (or Retail Generals path)
 - Port skeleton and sections; strip GMX-only properties/sections/examples
 - Replace version flags with Retail ones; use Retail examples
 - Re-run link pass for Retail paths; update Source Files to Retail-only if needed
 - Run full Final validation checklist for the Retail doc
 - Add Status/Reviewers and Document Log entries for the Retail doc
 
### Richness and Parity Requirements (CRITICAL)
- Parity with strongest reference: When documenting a derived/similar entity, mirror the Usage and Notes depth of the richest related doc (e.g., `ImmortalBody` should match `ActiveBody`’s Usage/Notes scope where behavior is shared). If content is intentionally omitted, add a one-line justification in Notes.
 - Retail↔GMX mirror parity (CRITICAL): For features available in both GMX and Retail, ensure the Retail mirror has equivalent depth to the GMX doc for all shared functionality. Explicitly copy and adapt shared Usage bullets, Notes, and Template inline comments. Differences should only reflect version-specific availability, not content quality.
- Section completeness gates (block merge if missing):
  - Overview, Table of Contents
  - Properties (with per-property inline Example lines)
  - Usage with three subsections: Limitations, Conditions, Dependencies
  - Template with concise inline comments for every line
  - Notes
  - Source Files (base class first)
  - Changes History and Document Log
  - Status and Reviewers
- Minimum content rules:
  - Examples: ≥2 for simple modules; 4–5 for complex/base entities
  - Notes: ≥5 bullets for modules with gameplay interactions
  - Usage must include ObjectExtend/ObjectReskin behavior when applicable
- Reference doc alignment step: If a doc inherits or shares behavior (e.g., `ImmortalBody` → `ActiveBody`), copy relevant shared bullets (adapt/adapt the text) into Usage/Notes rather than only linking.

### Reviewer Checklist (Expanded)
- Full TODO Flow present and followed (including Retail-specific TODO if applicable)
- Parity with base/peer doc verified (Usage/Notes richness, examples count, template comments)
- Per-property examples present; per-line template comments present
- All internal/external links valid; anchors exist; links outside backticks
- Version flags and availability lines correct everywhere
- Retail doc created/updated correctly (Retail-only content, flags, examples)
 - Retail↔GMX parity verified for shared functionality (no “poor content” in Retail mirror)
- Final Validation checklist items all satisfied; Richness and Parity requirements satisfied

### Optional Automation (Recommended)
- Diff-lint for parity: warn when a derived doc is missing sections/bullets present in its base reference doc
- Line-count/section-count heuristic: flag docs significantly shorter than base/peer without justification

### Block Merge Policy (CRITICAL)
- PRs must be blocked if any of the following fail:
  - Full TODO Flow step missing or not executed (including Retail-specific TODO when applicable)
  - Section completeness gates not met
  - Richness/Parity audit fails without documented justification
  - Final Validation checklist not fully satisfied

Execution rule: Generate this TODO in your workspace and follow it immediately without asking for approval. If new findings arise, update the TODO and continue.

**CRITICAL VERSION CHECKING PROCESS**:
- **MANDATORY**: Check ALL 4 versions in EXACT order: GMX Zero Hour → Retail Zero Hour 1.04 → GMX Generals → Retail Generals 1.04
- **DO NOT SKIP ANY VERSION**: Every property and enum must be checked against all 4 versions
- **DO NOT ASSUME**: Just because something exists in GMX Zero Hour does NOT mean it exists in GMX Generals
- **Verification method**: For each property/enum, check the actual source code (header files, parse tables) in each of the 4 version directories
- **Version flags must be accurate**: If a feature is only in GMX Zero Hour, use `Available only in: *(GMX Zero Hour)*`, NOT `Available only in: *(GMX Generals, GMX Zero Hour)*`

### Required Document Structure (All Docs)
Use this exact section order. Omit a section only if truly inapplicable.

- Title line: `# <Name>`
- Status line directly under title with certification stage, e.g.:
  - `Status: AI-generated, 0/2 reviews` (update as reviews happen)
- `## Overview`
- `## Table of Contents`
- `## Properties`
  - Group properties under clear categories (e.g., "Basic Settings", "Area Settings", "Upgrade Integration", "Target Selection").
  - Each property subsection must follow Property Format (below).
- `## Enum Value Lists`
- `## Examples`
- `## Usage`
  - Bold subsections (exact labels):
    - **Limitations**
    - **Conditions**
    - **Dependencies**
- `## Template`
- `## Notes`
- `## Modder Recommended Use Scenarios`
- `## Source Files`
- `## Changes History`
- `## Status`
- `### Reviewers`
 - `## Document Log`

**⚠️ CRITICAL REMINDER - AFTER COMPLETING THE DOCUMENT STRUCTURE:** Before considering the documentation complete, you MUST create or update the Retail mirror documentation file if the feature exists in Retail versions. This is a MANDATORY step (see step 5 in "Mandatory Research Workflow" and "Retail Mirror Documentation Files (Mandatory)" section). **DO NOT SKIP THIS STEP.**

### Section-by-Section Detailed Requirements
This expands what each section must provide and what to link.

#### Title
- Format: `# <Name>` (e.g., `# AutoHealBehavior`).
- If the entire feature is GMX-only, append `*(GMX)*` to the title.
- Immediately below add the Status line (see Status section) such as `Status: AI-generated, 0/2 reviews`.
 - Visual emphasis rule for GMX-only documents: When a document is entirely GMX-only (no Retail availability), color the title using a baby-blue span for quick recognition:
   - `# <span style="color:#5bbcff; font-weight:bold;">Name</span>`
   - Keep the standard availability line under the Overview (e.g., `Available only in: *(GMX Zero Hour)*`).

#### Overview
#### Section Headings and Availability
 - Use clear, descriptive section names (e.g., "Health Settings", "Damage Settings").
 - Place version flags on a new line under each heading or property.
 - Mixed-version documents (contain both GMX and Retail content): For GMX-only sections within these docs, color the section heading to make it stand out. Preferred format:
   - `### <span style="color:#5bbcff; font-weight:bold;">Section Name</span>`
   - Keep the standard "Available only in:" line immediately under the heading.
 - GMX-only documents (entire doc is GMX-only): Do NOT color individual section headings. Instead, color only the document title per the Title rule above.
- 2–5 sentences describing what the feature is and the gameplay it affects.
- State whether it is a one-per-game global block, a list of entries (many entries allowed), or a module added inside `Object`.
- If scope differs by game/version, include a one-line availability on a NEW LINE: `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)` or `Available only in: *(GMX)*`.
- **CRITICAL**: If something is available in Retail 1.04 (Retail Generals 1.04 or Retail Zero Hour 1.04), it is ALSO available in GMX. Always list both when applicable. Always specify which game variants (Generals vs Zero Hour) are included.

#### Usage
- Specify where the INI lives (root folder name like `Weapon`, global block like `GameData`, or inside `Object`).
- Clarify how many instances are allowed and how multiple instances interact (combine, overwrite, independent).
- Reference the Template section: “See Template for correct syntax.”
- Must include the three bold subsections:
  - **Limitations**: Mechanical boundaries and unsupported behaviors. Do NOT include detailed child entity limitations here - only brief mention with link to child entity documentation.
  - **Conditions**: Triggers, lifecycle, and multiple-instances behavior. Do NOT include detailed child entity conditions here - only brief mention with link to child entity documentation.
  - **Dependencies**: Required systems/types with links to their Docs pages. Do NOT include child entity dependencies here - child entities are documented separately.

#### Table of Contents
- Provide a bulleted list linking to all major sections and each property category.
- Use GitHub-style anchors and ensure headers are unique and stable.
- Example entries: `[Overview](#overview)`, `[Properties](#properties)`, and nested `- [Basic Settings](#basic-settings)`.

#### Properties
- Organize properties into meaningful categories. If a category is version-limited, add version flags in the category header.
- For each property, use the Property Format exactly (header with version flags, Type, Description, Default, Example).
- **CRITICAL**: Verify property names match exactly what appears in the parse table (`buildFieldParse` method) - do not use outdated or incorrect names.
- **CRITICAL**: Verify defaults from constructors/member initializers in the source code—do not guess. Read the constructor implementation to see actual initialization values.
- **CRITICAL - Link properties that reference other documented entities**: When a property references another documented entity/type (e.g., upgrade names, weapon names, FXList names, object names, etc.), you MUST link to that entity's documentation in the Type field. Properties may accept a single name or a list of names — reflect that in the Type text. Examples:
  - Properties that accept upgrade names (e.g., `TriggeredBy`, `ConflictsWith`, `RequiredAnyUpgradeOf`, `RequiredAllUpgradesOf`, `RemovesUpgrades`) → link to [Upgrade documentation](../Upgrade.md) and indicate singular/list: `Upgrade name or list of upgrade names (see [Upgrade documentation](../Upgrade.md))`
  - Properties that accept FXList names (e.g., `FXListUpgrade`) → link to [FXList documentation](../FXList.md): `FXList` (see [FXList documentation](../FXList.md))
  - Properties that accept weapon names → link to [Weapon documentation](../Weapon.md) and indicate singular/list where applicable: `Weapon name or list of weapon names (see [Weapon documentation](../Weapon.md))`
  - Properties that accept object names → link to [Object documentation](../Object.md) and indicate singular/list where applicable: `Object name or list of object names (see [Object documentation](../Object.md))`
  - This applies to ALL properties that reference other documented entities — they must be linked to their respective documentation files, and the Type must state whether the property accepts a single reference or a list.
- Link complex types to their Docs pages (e.g., `weapon` → `Docs/Weapon.md`, `FXList` → `Docs/FXList.md`).
- If a property uses an enum, add "Available Values: see [EnumName Values](#enumname-values)".

#### Inheritance Rules (Mandatory)
- **CRITICAL**: Modders do not need to understand inheritance or base classes. Documentation must be self-contained and complete.
- If the documented class/module/entity inherits from a base that defines INI properties, the derived doc MUST include ALL base class properties with FULL documentation (Type, Description, Default, Example, Available Values for enums) exactly as they appear in the base class documentation.
  - Example: `WeaponComponent` inherits `Component` → `WeaponComponent.md` must duplicate every property from `Component.md` with complete details (not just a list or link), plus any `WeaponComponent`-specific properties.
  - **Do NOT mention "inherited from", "base class", or "inherited properties" anywhere in the Properties section.** Present all properties as if they belong directly to the documented class/module/entity.
  - **Include full enum value lists** in the derived doc (copy from base), do NOT link to base enum sections. Modders should see all enum values directly.
  - Apply this rule to all feature types: global entities, entry catalogs, modules, components, and any nested templates.
- In `## Source Files`, list the base class first (for developer reference only, not for modder consumption).
- If multiple bases define properties, include properties from each base (group by category to keep clarity, but do not label them as "inherited" or mention base classes).
- When a base property is overridden or behaves differently in the derived class, clearly state the differences under the derived property without referencing the base.
- Property categories should describe functionality (e.g., "Health Settings", "Damage Settings") not inheritance structure.

### Cross-Usage Research — Mandatory
- **CRITICAL**: You MUST comprehensively research where the class/module/entity is USED throughout the ENTIRE codebase. Missing even one system interaction makes the documentation incomplete and misleading for modders.
- Search strategy — use MULTIPLE approaches:
  1. **Direct name searches**: Search for the class/type name across all systems.
  2. **Method/function searches**: Search for methods that use the class (e.g., lookup methods, status checks, modification methods, interaction handlers).
  3. **Property searches**: Search for INI property names that reference the class (e.g., properties that accept entity names, properties that check entity status, properties that configure entity interactions).
  4. **Interface searches**: Search for interfaces/abstract classes the feature implements or extends.
  5. **Grep for patterns**: Use grep to find all call sites, not just declarations.
- **Research patterns to identify**:
  - **Direct usage**: Other systems that directly reference or call methods on the documented entity.
  - **Property-based references**: INI properties in other entities that reference the documented entity by name or type.
  - **State checks**: Systems that check the status, state, or condition of the documented entity.
  - **Modification interactions**: Systems that modify, heal, damage, enable, disable, or otherwise alter the documented entity.
  - **GUI/Command integration**: Commands or GUI elements that interact with the documented entity.
  - **Prerequisite/Requirement systems**: Systems that check for the existence, absence, or status of the documented entity.
  - **Visual/Display systems**: Systems that display or render information about the documented entity.
  - **Specialized interactions**: Version-specific or feature-specific interactions (e.g., jamming, repair, upgrade systems).
- **CRITICAL - Getter/Setter and indirection awareness**: Do not assume properties are only used where parsed. Always scan for getter/setter methods and indirections that access the parsed data (e.g., `getX`, `setX`, `hasX`, `consumeX`, UI queries). Many systems interact only through these accessors. Document behaviors discovered via these methods.
- **For each discovered interaction**, determine whether it's a **Limitation**, **Condition**, or **Dependency** and document accordingly.

### Cross-Usage Interactions Checklist (Mandatory)
Before finalizing any doc, validate interactions with these common systems and add findings to Usage (Limitations/Conditions/Dependencies) with links:
- Weapons: Inventory use via `ConsumeInventory` (see [Weapon documentation](../Weapon.md)); clip reload effects and ammo pips.
- Locomotor: Fuel consumption via `ConsumeItem` and `ConsumeRate` (see [Locomotor](../Locomotor.md)).
- AI/Updates: Movement/flight logic (e.g., [JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)) that reacts to inventory/fuel presence.
- Resupply systems: [ParkingPlaceBehavior](../ObjectBehaviorsModules/ParkingPlaceBehavior.md), [AutoSupplyItemBehavior](../ObjectBehaviorsModules/AutoSupplyItemBehavior.md).
- Commands/UI: [CommandButton](../CommandButton.md) for resupply actions, costs, and availability; control bar UI displays.
- Game flow glue: Dispatch/handlers that implement resupply or costs (e.g., clip-first then top-up behavior, total cost from per-item cost).
- Upgrades: [InventoryUpgrade](../ObjectUpgrades/InventoryUpgrade.md) that can add items or change costs.

When scanning, search for patterns: the entity name, property strings, and methods like `get*`, `set*`, `has*`, `consume*`, `add*`, `set*Count`, and UI references.

### Usage Section — Required Content and Categorization
- Reference the [Template] section for syntax.
- Include three distinct sub-sections with NO duplication between them. Categorize each item correctly:

- **CRITICAL - Internal property linking**: When mentioning properties anywhere in the document (Usage, Overview, Notes, Properties descriptions, Examples text, etc.) — link those property names to their headers within the same document using `[PropertyName](#propertyname)`. Do not leave property names as plain text or inside backticks when they should be clickable links. **Exception**: Code snippets (```ini, ```cpp, etc.) cannot contain markdown links, so property names in code blocks remain as plain text. Example: "when [TriggeredBy](#triggeredby) is set" (CORRECT) vs "`TriggeredBy`" (WRONG outside code blocks).

#### Limitations
- **What belongs here**: Hard structural requirements that prevent the feature from existing or functioning AT ALL without them, including internal validation and logic constraints.
- **Must document**: Any validation, constraints, or internal logic that can cause the feature to fail, behave incorrectly, or produce unexpected results.
- **CRITICAL METHODOLOGY**: Read the actual parsing code, validation logic, and initialization code for each entity/module carefully. Do NOT follow patterns or assumptions. Each class may have unique behavior that must be discovered by examining:
  - Parsing functions (`parse*` methods) — check for default value assignments, validation checks, empty token handling
  - Initialization code (constructors, `init*` methods) — check for constraints, clamping, default behaviors
  - Validation logic (condition checks, range checks, null checks) — check for early returns, error conditions, fallback behaviors
  - Lookup/resolution code (lookup methods, find methods, resolve methods) — check for first-match behavior, duplicate handling, missing item behavior
- **Discovery process pattern**: When documenting naming rules or property validation, read the actual parsing function in the source file. Look for:
  - Does it check for empty values and return early?
  - Does it check for null/empty tokens and assign a default?
  - What default value is assigned, if any?
  - Are there uniqueness constraints (e.g., names must be unique within a scope)?
  - Are there format requirements (e.g., naming conventions, reserved names)?
  - This same careful reading applies to ALL properties, not just naming — each may have unique validation, defaults, or constraints.
- **NOT dependencies**: If something can exist without it (just won't work well), it's usually a Condition or Dependency.

#### Conditions
- **What belongs here**: Optional configuration or runtime state that changes HOW the feature behaves, but the feature can still exist/function without it.
- **Pattern examples**:
  - "If this entity's name is listed in another entity's property that references it, the entity's status affects that system's behavior" — the entity works fine, but the interaction only occurs if explicitly listed.
  - "When the entity's state changes (damaged/destroyed/enabled/disabled), visual or behavioral changes occur based on state properties" — runtime behavior based on entity state.
  - "If a property is set to a specific value, the entity behaves differently" — conditional behavior based on configuration.
- **NOT dependencies**: Optional interactions that modify behavior, not requirements for basic functionality.

#### Dependencies
- **What belongs here**: External features that MUST exist for this feature to be useful/functional. Without the dependency, the feature is broken or useless.
- **Critical rule**: Each dependency MUST include a description explaining WHY it is needed and what happens if missing.
- **Pattern examples**:
  - **Flag-setting dependency**: "EntityA sets a flag/status, but the actual functionality is handled by EntityB. Without EntityB, EntityA does nothing — the flag is set but never read."
  - **Parent container dependency**: "This child entity requires a parent container entity to exist. Without the parent, the child cannot be parsed or added."
  - **System dependency**: "This feature requires a specific system module to function. Without the system, the feature's properties are ignored or cause errors."
- **Format**: 
  - List the dependency with link to its documentation.
  - Explain WHY it's needed (what happens if missing).
  - Include exact property names when relevant (e.g., properties that reference the dependency).
- **DO NOT include**: Optional interactions that just change behavior (those go in Conditions). Requirements for existence (those go in Limitations).

### Module Placement and Behavior Rules (Mandatory for All Modules/Behaviors/Components)
**CRITICAL**: All modules, behaviors, and components must document their placement rules and behavior with Object, ObjectExtend, and ObjectReskin. This is a common pattern that applies to ALL module documentation.

**Placement Documentation Requirements**:
- **For all modules/behaviors/components**: Document where they can be placed (Object, ObjectExtend, ObjectReskin) and any restrictions.
- **Placement section format**: Add a "Placement" subsection at the start of the Usage section, immediately after the opening usage statement.

**Standard Placement Rules**:
1. **Object entries**:
   - **Retail**: All modules can be added to `Object` entries.
   - **GMX**: All modules can be added to `Object` entries.
   - **Duplicate module restriction**: Some module types (like body modules) can only exist once per object. If multiple instances of such modules are added, the game will crash with an assertion error (e.g., "Duplicate bodies", "Duplicate containers", "DuplicateStealthUpdates!", etc.). Document this in Limitations if applicable.

2. **ObjectExtend entries** (GMX only):
   - **GMX only**: ObjectExtend exists only in GMX (both Generals and Zero Hour). Do NOT mention ObjectExtend in Retail mirror documentation.
   - **Module replacement behavior**: When a module is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules (see `ThingTemplate.cpp` lines 345-357).
   - **Documentation**: Document in Conditions section: "**ObjectExtend (GMX only)**: When [ModuleName] is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's [ModuleName] module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules."

3. **ObjectReskin entries** (both Retail and GMX):
   - **Both versions**: ObjectReskin exists in both Retail and GMX.
   - **Module behavior**: ObjectReskin uses the same module system as Object. It does NOT support automatic module replacement like ObjectExtend.
   - **Duplicate module tag error**: Adding a module to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement.
   - **Documentation**: Document in Conditions section: "**ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding [ModuleName] to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend."

**Special Module Type Restrictions**:
- **Body modules** (ActiveBody, InactiveBody, StructureBody, etc.): Only one body module can exist per object. If multiple body modules are added to the same object, the game will crash with a "Duplicate bodies" assertion error during object creation. This restriction applies regardless of `ModuleTag` names — the object can only have one body module total (see `Object.cpp` lines 349-354 for Retail, lines 460-465 for GMX).
- **Container modules**: Only one container module can exist per object. Multiple containers will cause a "Duplicate containers" assertion error.
- **StealthUpdate**: Only one StealthUpdate can exist per object. Multiple instances will cause a "DuplicateStealthUpdates!" assertion error.
- **AI modules**: Only one AI module can exist per object. Multiple instances will cause an assertion error.
- **PhysicsBehavior**: Only one PhysicsBehavior can exist per object. Multiple instances will cause an assertion error.

**Documentation Format Example**:
```markdown
## Usage

Place under `[ModuleType] = [ModuleName] ModuleTag_XX` inside `Object` entries. In GMX, [ModuleName] can also be added to `ObjectExtend` entries. See Template for correct syntax.

**Placement**:
- **Retail**: [ModuleName] can only be added to `Object` entries .
- **GMX**: [ModuleName] can be added to both `Object` and `ObjectExtend` entries.

[Additional restrictions for special module types - e.g., "Only one body module can exist per object..."]

**Limitations**:
[...]

**Conditions**:
- **ObjectExtend (GMX only)**: When [ModuleName] is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's [ModuleName] module is automatically replaced...
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding [ModuleName] to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error...
```

**For Child Entity Documentation** (applies to all parent/child relationships):
- **Placement**: Explicitly list all parent entities that support the child entity with links. Do NOT use "inherit" terminology - modders don't understand inheritance. Instead, list the parent entities explicitly: "The following parent entities support [ChildEntityName]: [ParentA](../PathToParentA.md), [ParentB](../PathToParentB.md), [ParentC](../PathToParentC.md)."
- **Limitations**: List the same parent entities explicitly with links. Do NOT use "inherit" terminology. Use: "Requires one of the following parent entities: [ParentA](../PathToParentA.md), [ParentB](../PathToParentB.md), [ParentC](../PathToParentC.md); [ChildEntityName] cannot exist outside a parent entity block."
- **Multiple instances**: State the scope correctly (e.g., "Multiple [ChildEntityName] instances can be added to the same [ParentEntityName]") - child entities are scoped to their direct parent, not to a grandparent or container.
- **Naming**: Document naming uniqueness requirements (e.g., "[ChildEntityName] names must be unique within the same [ParentEntityName]") - ensure the scope matches the actual parent/child relationship.
- **Higher-level placement rules**: Do NOT mention ObjectExtend, ObjectReskin, or other higher-level placement rules in child entity documentation if they affect the parent entity, not the child directly. This information belongs in parent entity documentation, not child entity documentation.

**For Retail Mirror Documentation**:
- Remove all ObjectExtend references (GMX only).
- Keep ObjectReskin references (exists in both Retail and GMX).
- Adjust placement section to reflect Retail-only capabilities.
- Do NOT create Retail mirror documentation for GMX-only features (e.g., components are GMX Zero Hour only, so no Retail mirror).

### Linking Rules for Cross-Usage — Mandatory
- When you mention another documented feature, link to its documentation file. If the specific property is documented with an anchor, link directly to the property anchor. If not yet documented, link to the top of that doc file until it is completed.
- Use clear text that includes the INI property name exactly as it appears in the parse table (e.g., `AffectedByComponents`, `EngineComponentName`, `PrimaryComponentDamage`, `SecondaryComponentDamage`).

### Internal Linking — Mandatory (Within the Same Document)
- **CRITICAL RULE**: Whenever you mention a property or enum that is documented in the same file, link to its section header in ALL sections:
  - **Applies to**: Overview, Usage (including Limitations, Conditions, Dependencies), Notes, Properties descriptions, Enum Value Lists descriptions, Examples text, Modder Recommended Use Scenarios, Template comments, etc.
  - **Exception**: Code snippets (```ini, ```cpp, ```python, etc.) cannot contain markdown links, so property/enum names in code blocks remain as plain text without links.
  - Link properties by their header anchor (e.g., `[HealingType](#healingtype-gmx)`).
  - Link enum names to their enum section anchors (e.g., `[ComponentHealingType Values](#componenthealingtype-values)`).
- **CRITICAL RULE**: Links must ALWAYS be outside of backticks. Markdown links inside backticks do not work.
  - **INCORRECT**: `` `[Object](../Object.md)` `` or `` `[MaxHealth](#maxhealth)` ``
  - **CORRECT**: `[Object](../Object.md)` or `[MaxHealth](#maxhealth)` (link outside backticks, only property/command names inside backticks)
  - **Example**: "For `[AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md)` to heal" → **WRONG** (link inside backticks)
  - **Example**: "For [AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md) to heal" → **CORRECT** (link outside backticks)
  - **Example**: "If [MaxHealth](#maxhealth) is 0" → **CORRECT** (internal link outside backticks)
  - **Example**: "The `MaxHealth` property" → **CORRECT** (property name only, no link, so backticks are fine)
  - Only use backticks for property names, command names, enum values, or code snippets that are NOT links.
- The goal is effortless navigation for modders - every property/enum mention should be clickable (except in code blocks).

### Internal Anchors and Linking (Critical)
- Do NOT rely on auto-generated anchors; they vary by renderer and can break when headers change.
- Always add a manual anchor immediately before any section that will be linked internally.
  - Format: `<a id="anchor-name"></a>` on its own line.
  - Example before a header:
    - `<a id="hitside-values"></a>` then `#### `HitSide` Values`
    - `<a id="bodydamagetype-values"></a>` then `#### `BodyDamageType` Values`
- Put version/availability on a NEW LINE directly under the header using the exact text: `Available in: *(...)*` or `Available only in: *(...)*` (not `Availability:`).
  - **CRITICAL**: Always check all 4 versions in order: GMX Zero Hour → Retail Zero Hour → GMX Generals → Retail Generals. Do NOT assume availability.
  - **CRITICAL**: Always specify which game variants (Generals vs Zero Hour) are included. Use one of these formats:
    - **Available in 2 or more versions**: `Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*` or shorter `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)` or `Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*`
    - **Available only in exactly 1 version**: `Available only in: *(GMX Zero Hour)*` or `Available only in: *(Retail Generals 1.04)*`
  - **CRITICAL**: If something is available in Retail 1.04 (Retail Generals 1.04 or Retail Zero Hour 1.04), it is ALSO available in GMX. Always list both when applicable.
  - Example:
    - `#### `BodyDamageType` Values`
    - `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)`
  - For GMX-only features (multiple variants): `Available in: *(GMX Generals, GMX Zero Hour)*`
  - For GMX-only features (single variant): `Available only in: *(GMX Zero Hour)*`
  - For Retail-only features (rare): `Available only in: *(Retail 1.04)* (Generals, Zero Hour)` (but verify this is truly not in GMX)
- When referencing inside the same document, always link as `[text](#anchor-name)` using the manual id.
- Apply manual anchors and `Available in:` lines to ALL sections that need version flags (Enums, Properties groups, entire sections, Overview section, etc.), not just enum values.

### External Linking — Specific Systems
- When referencing specific systems, entities, or commands, link to their docs using this pattern: `[SystemOrDocName](relative/path/to/Doc.md)`.
  - **CRITICAL RULE**: Links must ALWAYS be outside of backticks. Never put markdown links inside backticks.
    - **INCORRECT**: `` `[EntityName](../PathToEntity.md)` `` (link inside backticks - will not work)
    - **CORRECT**: [EntityName](../PathToEntity.md) (link outside backticks - will work)
    - If you need to emphasize the link text, use the link alone, or use backticks only for inline code terms (property names, enum values) that are NOT links.
  - **Pattern**: Link every mention of a documented entity, system, or command to its documentation. Examples of when to link:
    - When mentioning command types or constants that reference the entity.
    - When discussing interactions with other systems that use the entity.
    - When referencing behaviors or modules that interact with the entity.
    - When mentioning properties in other entities that reference the documented entity.
    - When discussing systems that modify, check, or display the entity.
  - Follow the same linking pattern for all referenced systems — link the entity name, not just the mention.

#### Enum Value Lists — Completeness (GMX-first)
- For each enum, create a subsection with version flags and a source reference (header path/link).
- If there is a corresponding string array, note it and maintain the same order as the enum.
- List EVERY value with individual inline version flags and a short description — do not stop at the Retail set.
- **CRITICAL**: Check all 4 versions in order: GMX Zero Hour → Retail Zero Hour → GMX Generals → Retail Generals. Enumerate the complete GMX set first, then mark which values exist in Retail.
- GMX-first rule: enumerate the GMX set first; mark GMX-only values with inline format like `*(GMX Zero Hour)*` and values that also exist in Retail with `*(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*`.
- **Pattern for enum discovery**: Start with the GMX Zero Hour header file that defines the enum. Extract ALL enum values, then check each value against Retail versions to determine availability. Do NOT assume Retail has the same set — GMX may have significantly more values than Retail. For example, if GMX has 48 values and Retail has only 4, document all 48 with proper version flags.
- **Pattern for enum versioning**: If an entire enum exists only in GMX (not in Retail), set the section header to `Available only in: *(GMX Zero Hour)*` (or appropriate GMX version) and mark each value with the same version flag. If an enum exists in multiple versions but with different value counts, document all values with individual version flags.

#### Examples
- **Minimum example count** (based on property count):
  - **Entities with more than 2 properties**: Provide at least 5 examples to demonstrate various property combinations and usage scenarios.
  - **Entities with 2 or fewer properties**: Provide 1-2 examples sufficient to show basic usage.
  - **Components/modules with no properties**: Provide 1 example showing the basic structure is enough.
- **Child entity examples in parent documentation (MANDATORY)**: For each child entity property in the Properties section of parent documentation, you MUST include exactly 1 example directly under the child entity property description. The example should demonstrate basic usage of that child entity type. Do NOT include child entity examples in the Examples section of the document — only in the Properties section under each child entity property. Child entities are documented separately in their own files, but parent documentation should include a brief example for each child entity type to show how they are added. This applies to ALL parent/child relationships found in the codebase. Examples of parent/child patterns include: nested entities within parent entities, list items within container entities, and module blocks within object entries. Additional parent/child patterns may be discovered when documenting other features.
- Remove all INI comment lines from examples.
- Prefer GMX examples from `Patches/WW2030/INI`, then Retail from `Sources/Generals` (Retail Generals 1.04) or `Sources/Zero Hour` (Retail Zero Hour 1.04).
- Examples should illustrate typical usage, edge cases, and property combinations.
- For catalogs: show multiple entries. For modules: show embedding inside `Object` with `ModuleTag_*`.

#### Template
- Provide a canonical copy-paste block in ```ini fences.
- Include important properties with default values and concise comments ending with version flags.
- **Child entity references in templates**: Do NOT include detailed child entity templates in parent documentation templates. Instead, include only a brief comment indicating child entities can be added (e.g., `; [ChildEntityName] entries can be added here (see [ChildEntityName] documentation)`, with version flags if applicable). Child entities are documented separately in their own files. This applies to ALL parent/child relationships found in the codebase. Examples of parent/child patterns include: nested entities within parent entities, list items within container entities, and module blocks within object entries. Additional parent/child patterns may be discovered when documenting other features.
- Use the correct opener for modules/components: `Behavior = ...`, `Collide = ...`, or `SpecialPower = ...`.
- For one-per-game global blocks: wrap with the correct block name such as `AIData`, `GameData`, or `multiplayer`.

#### Notes
- Bullet points with practical tips, caveats, performance considerations, and non-obvious interactions.
- Avoid repeating Usage; focus on operational knowledge for modders.
- **Child entity notes in parent documentation**: Do NOT include detailed child entity-specific notes in parent documentation. Child entity details belong in child entity documentation files. Only include a brief mention that child entities can be added with a link to child entity documentation. This applies to ALL parent/child relationships found in the codebase. Examples of parent/child patterns include: nested entities within parent entities, list items within container entities, and module blocks within object entries. Additional parent/child patterns may be discovered when documenting other features.

#### Modder Recommended Use Scenarios
- **Leave empty by default**: This section should be left empty with `(pending modder review)` placeholder. Modders will fill this section based on their experience and use cases. Do NOT write scenarios unless explicitly requested.

#### Source Files
- First line must show the base class (if any): `**Base Class:** [ClassName](../../path/to/header.h)`. If the base class exists in both GMX Generals and GMX Zero Hour, list both: `**Base Class:** [ClassName](../../GeneralsMD/path/to/header.h) (GMX Zero Hour), [ClassName](../../Generals/path/to/header.h) (GMX Generals)`.
- Then list GMX header and source files as **clickable links** (relative paths from `Docs/`), not just backticks. **CRITICAL**: Include BOTH GMX Generals and GMX Zero Hour source files if they exist in both versions.
- Format for files that exist in both versions:
  - `- Header (GMX Zero Hour): [FileName.h](../../GeneralsMD/path/to/header.h)`
  - `- Source (GMX Zero Hour): [FileName.cpp](../../GeneralsMD/path/to/source.cpp)`
  - `- Header (GMX Generals): [FileName.h](../../Generals/path/to/header.h)`
  - `- Source (GMX Generals): [FileName.cpp](../../Generals/path/to/source.cpp)`
- Format for files that exist in only one version:
  - `- Header: [FileName.h](../../GeneralsMD/path/to/header.h)` (if GMX Zero Hour only)
  - `- Header: [FileName.h](../../Generals/path/to/header.h)` (if GMX Generals only)
- **CRITICAL**: Header and source entries must be markdown links `[filename](path)`, NOT just backticks. The instruction says "link to header/source paths" — this means actual clickable links.
- If Retail differs, add a short note of the Retail path or name (no external links for Retail mirror files).
- Use backticks for inline names of `classes` and `functions` in descriptions, but file paths should be links.

#### Changes History
- Track feature changes/additions in the game code after Retail 1.04 (e.g., GMX-added properties, new sections, extended enums). Do not list documentation edits here.

#### Document Log
- Track documentation events (initial creation, refactors, link fixes) separate from feature changes.

#### Status
- Simple block with:
  - `- Documentation Status: AI-generated | In Review | Certified`
  - `- Last Updated: DD/MM/YYYY by @author`
  - `- Certification: X/2 reviews`
- Keep this consistent with the status line under the title.

#### Reviewers
- Bullet list of reviewers with handle, date, and brief verification note.
- Example: `- @ReviewerA — 03/11/2025 — Verified defaults and enums`.

### Property Format (Mandatory)
For every property in `## Properties`:

#### `PropertyName`
Available in: *(version information)* or Available only in: *(version information)*

- **Type**: `<Type>` (link to doc for complex types; see Cross-References). **CRITICAL**: Keep the type name in backticks, but put the link OUTSIDE the backticks so the link works. Example: `- **Type**: weapon` (see [Weapon documentation](../Weapon.md)) — NOT `- **Type**: weapon (see [Weapon documentation](../Weapon.md))` (link inside backticks won't work)
- **Description**: Practical effects, not code internals. For booleans: what happens when Yes vs No. For numbers: impact of larger vs smaller values. For percentages: scale meaning (1.0 vs 100% according to parser). Mention constraints and edge cases.
- **Default**: `<value>` as initialized in code (constructor or member init) or parse fallback.
- **Example**: `PropertyName = <value>`

**CRITICAL**: Version information must be on a NEW LINE directly under the property header, using the exact format:
- **Use "Available in:" when listing 2 or more versions**: `Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*` or shorter `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)` or `Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*`
- **Use "Available only in:" when listing exactly 1 version**: `Available only in: *(GMX Zero Hour)*` or `Available only in: *(Retail Generals 1.04)*`
- **CRITICAL**: Always check all 4 versions in order: GMX Zero Hour → Retail Zero Hour → GMX Generals → Retail Generals. Do NOT assume availability. If checking shows it's in multiple versions, use "Available in:". If it's in exactly 1 version, use "Available only in:".

Always specify which game variants (Generals vs Zero Hour) are included when applicable. Do NOT put version flags inline in the header like `#### PropertyName *(GMX)*` — use the "Available in:" or "Available only in:" line format instead.

Category headers should include version flags where the entire category is version-limited, using the same new-line format.
 
When the property uses an enum or indexed list parser (e.g., `INI::parseIndexList`):
- Add `Available Values: see [EnumName Values](#enumname-values)` and ensure the property text links to that section.
- Clarify that modders must use the string names from the enum name array (e.g., `"PRESERVE_RATIO"`) rather than C++ enum tokens. Use the exact spelling/case from the array.

When the property uses a custom parser (not `INI::`), summarize its behavior (accepted syntax, lists, complex types, validation/normalization) and link any referenced entities (e.g., `[Object](Object.md)`, `[Upgrade](Upgrade.md)`).

### Enum Format (Mandatory)
In `## Enum Value Lists`, for each enum:

#### `EnumName` Values
Available in: *(version information)* or Available only in: *(version information)*

- Source reference: header file path in backticks or a link in the same line.
- List every value with individual inline version flags and a short description.
- **CRITICAL**: Enum section header uses new-line format (as shown above), but enum values in the list use inline format: `*(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*` or `*(GMX Generals, GMX Zero Hour)*` or `*(GMX)*`.
- If there is a corresponding string array, ensure order matches the enum declaration.

z #### Special Enum Documentation Files
**CRITICAL**: Some enums have their own dedicated documentation files and should NOT have their details listed in the Enum Value Lists section of other documents. Instead, link to the dedicated enum documentation file.

The following enums have their own documentation files:
- **`KindOfMaskType`** (KindOf) - See [KindOf documentation](KindOf.md)
- **`ModelConditionFlagType`** (ModelConditionFlags) - See [ModelConditionFlagType documentation](ModelConditionFlagType.md)

**For new documentation**: When documenting a property that uses one of these enums, do NOT include the enum value list in your document's `## Enum Value Lists` section. Instead:
- In the property's `Type` field, link to the enum documentation: `KindOfMaskType` (see [KindOf documentation](KindOf.md)) or `ModelConditionFlagType` (see [ModelConditionFlagType documentation](ModelConditionFlagType.md))
- In the property description, reference the enum documentation when needed
- Remove any enum value list sections for these enums from your document

### Versioning Rules (Mandatory)
- **CRITICAL**: Version information must be on a NEW LINE for properties, enums, enum sections, and major sections — NOT inline in headers.
- **CRITICAL**: Always specify which game variants (Generals vs Zero Hour) are included. The four versions are:
  - GMX Generals
  - GMX Zero Hour
  - Retail Generals 1.04
  - Retail Zero Hour 1.04
- **CRITICAL**: If something is available in Retail 1.04 (Retail Generals 1.04 or Retail Zero Hour 1.04), it is ALSO available in GMX. Always list both when applicable.
- Use these exact formats:
  - **Available in 2 or more versions**: `Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*` or shorter `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)` or `Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*`
  - **Available only in exactly 1 version**: `Available only in: *(GMX Zero Hour)*` or `Available only in: *(Retail Generals 1.04)*`
  - **Game-specific (multiple versions but same game)**: `Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*` (both Zero Hour variants)
  - **CRITICAL**: Use "Available in:" for 2+ versions, "Available only in:" for exactly 1 version. Always check all 4 versions: GMX Zero Hour → Retail Zero Hour → GMX Generals → Retail Generals.
- For enum values (inline in list):
  - Use inline format: `*(GMX, Retail 1.04)*` or `*(GMX)*` or `*(Retail Zero Hour 1.04 only)*`
- For `Available in:` / `Available only in:` lines under section headers (enums, property categories, Overview, properties):
  - Use full new-line format as described above.
  - **CRITICAL**: If a feature exists in Retail 1.04, write `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)` not just `*(Retail 1.04)*`.
- At the top of each doc Overview section, include availability if scope differs by game:
  - Example: `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)` or `Available only in: *(GMX)*`.
- When an entire entity/template is GMX-only, clearly mark the title line with `*(GMX)*` and use `Available only in: *(GMX)*` or `Available only in: *(GMX Generals, GMX Zero Hour)*` in the Overview.

### Cross-References (Mandatory)
- When a property references another documented class/type, link to the documentation in `Docs/` using relative paths, not the source code. Example:
  - `- **Type**: weapon` (see [Weapon documentation](../Weapon.md)) - Note: the type name is in backticks, but the link is OUTSIDE the backticks so it works
- In `## Source Files`, link to header/source paths for GMX (and note Retail paths if relevant).
- Use backticks for file/class/function names inline.
- **Internal property linking**: When a property or enum is mentioned anywhere in the document (Overview, Usage, Notes, Properties descriptions, Enum descriptions, Examples text, etc.), link it internally using `[PropertyName](#propertyname)` format. This applies to ALL sections of the document. **Exception**: Code snippets (```ini, ```cpp, etc.) cannot contain markdown links, so property/enum names in code blocks remain as plain text. **CRITICAL**: Keep links OUTSIDE backticks so they work. Example: If [InitialHealth](#initialhealth) exceeds [MaxHealth](#maxhealth), the value is clamped. In this example, the links are outside any backticks, while code values like `0.0` stay in backticks. **WRONG**: `` `[InitialHealth](#initialhealth)` `` or `` `If [InitialHealth](#initialhealth) exceeds [MaxHealth](#maxhealth)` `` (links inside backticks won't work). Use backticks only for code-like values like `0.0` or `Yes`, not for links.
- **External system references**: 
  - Use `[Locomotor](../Locomotor.md)` instead of `LocomotorTemplate` - modders don't know about template/data object structure, only the main entity name.
  - Use correct relative paths for update modules: `[JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)` (not `ObjectModules`).
- Link every mention of a documented entity/module/component everywhere in the doc (Overview, Usage, Properties, Enum Value Lists, Notes, Modder Scenarios). Do not leave raw names unlinked. Examples:
  - `[Object](Object.md)`, `[Upgrade](Upgrade.md)`, `[Weapon](Weapon.md)`, `[AutoHealBehavior](ObjectBehaviorsModules/AutoHealBehavior.md)`, `[FireWeaponCollide](ObjectModules/FireWeaponCollide.md)`.
- In Properties, if the description mentions another type or module (e.g., uses an `FXList` or requires `ActiveBody`), link those names in-line to their Docs pages.
- For enum-using properties, link the property's Available Values line to the enum section, and add a short note in the enum section mentioning which properties consume it.

### Reference Property Error Semantics (MANDATORY)
- For any property that references other entities (Object, Science, Upgrade, KindOf, Component, Item names), include a concise “Invalid references handling (from code)” note in Limitations/Notes. Use these rules:
  - Science: invalid names cause a hard load error (throws INI_INVALID_DATA) and prevent game start.
  - Upgrade: invalid names cause a hard load error (throws INI_INVALID_DATA).
  - Object template: invalid names trigger a debug assertion during name resolution; in non-debug builds behavior is undefined and may crash later (e.g., when generating requirement/conflict text). Treat as fatal; require valid names.
  - KindOf: invalid names abort parsing via index scanning; treat as fatal.
  - Inventory item names (free-form): not validated at load; conditions simply never match at runtime (effectively ignored).

### Property Parsing and Validation (Critical)
- Document how each property is parsed, referencing the specific field parse line when possible.
- Common parser patterns:
  - Numeric/string: `INI::parseReal`, `INI::parseInt`, `INI::parseUnsignedInt`, `INI::parseAsciiString`.
  - Time/frames: `INI::parseDurationUnsignedInt` (milliseconds or frames; reflect units in docs).
  - Boolean: `INI::parseBool` (values `Yes`/`No`).
  - Enum/index: `INI::parseIndexList` (paired with a name array like `TheMaxHealthChangeTypeNames`). Modders must use the string names from the array.
  - Complex/custom: e.g., `ObjectPrerequisite::parseObjectPrerequisites` (may parse lists, complex blocks, and perform validation/normalization). Summarize accepted syntax and link referenced entities.
- Include parser-driven constraints in the Description (clamping, defaults when omitted, required presence).
- For enums, identify the enum in headers (e.g., `MaxHealthChangeType`) and the exact name array. Present values using the name array strings and instruct to use those strings in INI.
 - Study both custom parsers and INI built-in parsers in code to fully understand:
   - Accepted input forms, edge cases, normalization, and validation paths.
   - Which member variables the parser fills (via `offsetof`) and how those members are later used in the class’ logic. Reflect this behavior succinctly in the property Description to guide modders on intended use.
 - If a parser produces or references other entities (objects, upgrades, FX, weapons, etc.), link those entities in-line to their Docs pages everywhere mentioned (e.g., `[Object](Object.md)`, `[Upgrade](Upgrade.md)`).
- In addition to parse tables, inspect all call sites where the parsed members are read/used. This is essential to understand how properties impact gameplay across systems (e.g., locomotor speed calculations using component status, weapons applying per-component damage).

### Examples (Rules)
- Use authentic examples from GMX first (`Patches/WW2030/INI`), then Retail sources.
- Remove all INI comments from examples.
- Use minimal but complete examples illustrating a specific concept.
- Provide multiple examples to cover different property combinations; align with complexity.
  - GMX examples from: `Patches/WW2030/INI/...`
  - Retail examples from: `e:\Games\Command and Conquer - Generals - Work\Generals Source\Sources\Generals\...\INI\...` (Retail Generals 1.04) or `e:\Games\Command and Conquer - Generals - Work\Generals Source\Sources\Zero Hour\...\INI\...` (Retail Zero Hour 1.04)
 - Include, where useful, side-by-side examples or notes highlighting differences between GMX and Retail (Generals/Zero Hour) to build a comprehensive picture of usage.

### Template (Rules)
- Wrap with ```ini code fences.
- Show all important properties with default values from code where applicable.
- Include concise inline comments describing each property and add version flags at the end of the comment, e.g.:
  - `Property = default_value      ; // description *(v1.04)*`
- For modules embedded in `Object`, use the exact module line format:
  - `Behavior = <BehaviorName> ModuleTag_XX` or `Collide = <ModuleName> ModuleTag_XX` or `SpecialPower = <ModuleName> ModuleTag_XX` as appropriate.
 - If the feature supports per-veterancy or per-level lists (e.g., `FireFX`), demonstrate the per-level pattern succinctly.

### Usage Section (Rules)
- Refer to the `## Template` for syntax; keep Usage concise.
- Include these three subsections under Usage:
  - **Limitations**: What cannot be done or boundaries.
  - **Conditions**: How/when it operates, multiple instances behavior.
  - **Dependencies**: Other systems/types needed (e.g., `ActiveBody`, `UpgradeMux`).

### Review and Certification Workflow (Mandatory)
1. Draft creation: Mark `Status: AI-generated, 0/2 reviews`.
2. At least two modders review for correctness and completeness:
   - Validate properties, defaults, enums, examples, and version flags against code and INI.
   - Ensure cross-links are correct and examples build logically.
3. After each review, update the Status line and add the reviewer to `### Reviewers` with date and brief note.
   - Example reviewer line: `- @ReviewerName — 03/11/2025 — Verified properties, added GMX flags`
4. When two independent reviewers approve, set: `Status: Certified, 2/2 reviews`.
5. If further revisions occur later, increment the denominator and numerator (e.g., `3/3`) and keep a brief note in `## Changes History`.

### Changes History (Rules)
- Maintain chronological entries with date, author, and short description.
- Use present tense: "Adds", "Fixes", "Clarifies".
- For GMX code changes that alter enums/properties, ensure the doc is updated in the same change set.

### Writing and Style Conventions
- Match the surrounding legacy style; prefer concise, practical descriptions for modders.
- Use backticks for `files`, `directories`, `classes`, `functions`, property names, command names, enum values, and code snippets that are NOT links.
- **CRITICAL**: Never put markdown links inside backticks. Links must be outside backticks to work.
  - **INCORRECT**: `` `[Object](../Object.md)` ``, `` `[MaxHealth](#maxhealth)` ``, `` `[CommandButton](../CommandButton.md)` ``
  - **CORRECT**: `[Object](../Object.md)`, `[MaxHealth](#maxhealth)`, `[CommandButton](../CommandButton.md)` (link outside backticks)
  - Use backticks only for non-link text like property names: "The `MaxHealth` property" or "Use `COMMAND_REPLACE_COMPONENT`"
- No executable code in docs; only references and INI snippets.
- Avoid speculative statements; only document behavior confirmed by code or shipped INI.
- Use consistent category names across similar modules.
 - Avoid developer jargon; prefer modder-friendly wording everywhere:
   - Say "one-per-game global block" instead of "singleton".
   - Say "list of entries" instead of "catalog".
   - Say "module added inside Object" instead of "embedded module".
 - Always link documented entities/modules/components wherever they are mentioned across all sections (Overview, Usage, Properties, Enum Value Lists, Notes, Modder Scenarios). Avoid bare names.

### Special Notes per Doc Family
- Global config (one block per game) (e.g., `AIData`, `GameData`, `multiplayer`):
  - Emphasize: one block per game; document defaults and common fields compactly.
  - Examples should show partial edits rather than redefining the whole file.
- Entry lists (e.g., `Science`, `ParticleSystem`, `Weapon`):
  - Clarify that multiple entries can exist; include examples for defining several.
  - For `Weapon`, note GMX differences if structure diverged from Retail and mark them.
- Modules/behaviors/components:
  - Must state they are added inside `Object` entries and cannot be standalone unless explicitly allowed by code.
  - Include base class line in `## Source Files` first.

### Version Flag Examples (Apply Everywhere)
- Property header with new-line format:
  - `#### `SkipSelfForHealing``
  - `Available in: *(GMX, Retail 1.04)* (Zero Hour only)`
- GMX-only property:
  - `#### `RadiusDamageAffectsMaxSimultaneous``
  - `Available only in: *(GMX Generals, GMX Zero Hour)*`
- Enum section header with new-line format:
  - `#### `WeaponPrefireType` Values`
  - `Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)`
- Enum value (inline format):
  - `- **`PER_SHOT`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* — Prefire delay for every shot`

### Minimal Author Checklist (Pre-PR)

**⚠️ CRITICAL FINAL CHECK BEFORE SUBMITTING: Did you create/update the Retail mirror documentation file? If the feature exists in Retail versions, you MUST create or update the Retail mirror file. This is MANDATORY, not optional.**

- **I read the entire instruction file completely from start to finish** before creating/editing the documentation.
- I checked all 4 versions in order (GMX Zero Hour → Retail Zero Hour → GMX Generals → Retail Generals) for properties and enums.
- I confirmed defaults and types directly in headers/sources.
- I added version flags to every property and enum/value.
- I linked to related Docs for all cross-referenced types, including properties that reference other documented entities (e.g., upgrade names, weapon names, FXList names, object names) - these must be linked in the Type field.
- **I verified all links are OUTSIDE of backticks** - markdown links inside backticks do not work. Check all internal property links (e.g., `[MaxHealth](#maxhealth)`) and external system links (e.g., `[ActiveBody](../ObjectModules/ActiveBody.md)`) are not inside backticks.
- I included multiple real examples without comments.
- I added a full `## Template` with defaults and flags.
- I wrote `## Notes` and `## Modder Recommended Use Scenarios`.
- I filled `## Source Files` with header/source links and base class line first.
- I duplicated and included inherited INI properties in derived docs (modules, entities, components).
- **I scanned for getters/setters and indirect usage** of properties (e.g., `get*`, `set*`, `has*`, `consume*`) across the codebase and documented discovered behaviors in Usage (Limitations/Conditions/Dependencies) as needed.
- **I completed the Cross-Usage Interactions Checklist** (Weapons, Locomotor, AI/Updates, Resupply systems, Commands/UI, Game flow glue/dispatch, Upgrades) and added all relevant interactions with links.
- **⚠️ I created/updated Retail Mirror Documentation files (MANDATORY if Retail features exist)** - This is a MANDATORY step. If the feature exists in Retail versions (Retail Generals 1.04 or Retail Zero Hour 1.04), I created or updated the Retail mirror file at `E:\Games\Command and Conquer - Generals - Work\Generals Source\CnC_Generals_Zero_Hour\ModdingDocs\...` (see step 5 in "Mandatory Research Workflow" and "Retail Mirror Documentation Files (Mandatory)" section). **DO NOT SKIP THIS STEP.**

### Submission Gate (Hard Requirements — Block Merge if any fail)
- Version matrix completed for ALL properties/enums/entities across the four versions in order: GMX Zero Hour → Retail Zero Hour 1.04 → GMX Generals → Retail Generals 1.04.
- Availability lines present and correct in Overview and each property category; GMX-only sections use colored heading ONLY in mixed-version docs; GMX-only docs color title only.
- Retail document created/updated when Retail features exist, with Retail-only content (no GMX properties) and Retail paths.
- Internal property linking applied in ALL sections (except code blocks). Cross-entity Type fields link to their docs and specify "name or list of names" where applicable.
- Changes History lists ONLY feature/code changes; Document Log lists documentation events.
- Cross-Usage checklist completed; getter/setter and indirect usages scanned and reflected in Usage (Limitations/Conditions/Dependencies).

### Example Status and Reviewers Blocks
- `## Status`
  - `- Documentation Status: AI-generated`
  - `- Last Updated: 03/11/2025 by @<author>`
  - `- Certification: 1/2 reviews`
- `### Reviewers`
  - `- @ReviewerOne — 03/11/2025 — Validated defaults`
  - `- @ReviewerTwo — 05/11/2025 — Cross-checked enums`

### Common Research Hotspots
- Parse tables: `The<Thing>FieldParseTable` or `INI::<parse>` in `.../Source/...`.
- Enums: headers in `Include/...`, string arrays in corresponding `.cpp`.
- Base classes: `Include/GameLogic/Module/` for behaviors, `Include/GameLogic/` for entities.

### Prohibitions
- Do not guess behavior; if uncertain, research more.
- Do not include executable code; only INI inside fenced blocks is allowed.
- Do not omit version flags even if availability seems obvious.
- **⚠️ DO NOT skip creating/updating Retail mirror documentation files** - This is a MANDATORY requirement, not optional. If Retail features exist, you MUST create or update the Retail mirror file.

---

**🚨 FINAL REMINDER BEFORE SUBMITTING: Did you create/update the Retail mirror documentation file? If the feature exists in Retail versions (Retail Generals 1.04 or Retail Zero Hour 1.04), you MUST create or update the Retail mirror file at `E:\Games\Command and Conquer - Generals - Work\Generals Source\CnC_Generals_Zero_Hour\ModdingDocs\...`. This is a MANDATORY requirement, not optional. DO NOT SUBMIT DOCUMENTATION WITHOUT COMPLETING THIS STEP IF RETAIL FEATURES EXIST.**

Adhering to this guide ensures consistent, accurate, and reviewer-certifiable documentation that modders can trust.


