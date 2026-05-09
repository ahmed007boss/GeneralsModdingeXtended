layout: page
title: "PAGE-TITLE"
permalink: /index

## Generals Modding Documentation Guide

Status: AI-generated, 0/2 reviews

### What is this documentation and its purpose?

This repository hosts the authoritative, living documentation for GMX (Generals Modding eXtended). The docs explain how gameplay systems, INI classes, modules, behaviors, and enums work. They are written for modders and contributors to:

- Provide precise, practical references for every feature and property
- Clarify version availability across Generals and Zero Hour variants
- Stay current with features, fixes, and deprecations as the code evolves
- Ensure consistency so identical concepts are described identically across files

What we expect from these docs:

- Accuracy: Mirrors current code and parse tables
- Completeness: All properties include type, description, default, example, and version flags
- Consistency: Shared text is standardized across related documents
- Modder-first language: Avoid internal function names and engine-internal jargon

### Generals versions and how to read them

GMX targets multiple code lines. Use version flags to indicate availability:

- GMX Generals: Features in GMX’s Generals code line
- GMX Zero Hour: Features in GMX’s Zero Hour code line
- Retail Generals 1.08: Features in original Generals
- Retail Zero Hour 1.04: Features in original Zero Hour

Use inline flags next to every property and enum value, for example:

- `*(GMX Generals)*`, `*(GMX Zero Hour)*`
- `*(Retail Generals 1.08)*`, `*(Retail Zero Hour 1.04)*`
- For new, unreleased items: `*(GMX Upcoming)*`

### Why this documentation lives in the community code repo

Documentation must evolve with the code. Keeping docs here ensures:

- Changes to code and docs can be reviewed together
- Docs stay synchronized with features, bugfixes, and removals
- CI and reviews can enforce structure and consistency
- Contributors can improve docs alongside their code changes

### How we create documentation (including AI involvement)

The process emphasizes correctness, review, and maintainability:

1) Code study
- Identify the class/behavior and its base class
- Read `buildFieldParse` and `FieldParse` tables in `.cpp`
- Cross-check member types and defaults in `.h`
- Note enums and their string tables

2) Drafting
- Write Overview, Usage (Limitations, Conditions, Dependencies)
- Document every property: Type, Description, Default, Example, Version flags
- Document enums: Full value list with flags
- Add Notes and a complete Template with inline comments

3) Versioning
- Compare GMX vs Retail variants
- Mark flags on every property and enum value

4) Examples and cross-links
- Provide realistic INI examples
- Cross-link referenced classes to their docs

5) Review cycle
- Self-review for consistency with related docs
- Peer review (aim for 2 approvals)
- Apply feedback, then mark Last Updated and Document Log

6) AI assistance
- AI may help draft or standardize language
- Authors must validate against source and fix inaccuracies
- Never include engine-internal function names in user-facing text

### Contributor guide: structure every document the same way

Each INI-parsable class or behavior document should include:

1) Overview
2) Usage
- Limitations
- Conditions
- Dependencies

3) Table of Contents

4) Properties
- One subsection per property with: Type, Description, Default, Example, Version flags
- For enums, add a dedicated “EnumName Values” section and link from properties

5) Examples

6) Template
- Use ```ini code blocks with inline comments
- Include version flags in comments
- Use default values from source initialization

7) Notes

8) Source Files
- List base class first
- Include links for GMX Generals and GMX Zero Hour when applicable

9) Changes History

10) Document Log
- Reset to a single line when first created: “- 16/12/2025 — AI — Initial document created.”

11) Status and Reviewers

Formatting and language standards:

- Use modder-friendly phrasing; avoid internal function names and code paths
- Use `Type: Alias (see [DocName](RelativePath.md))` for cross-references
- Keep shared text identical across related body modules
- Keep headings concise and scannable

### Document Log

- 16/12/2025 — AI — Initial document created.

### Status

- Documentation Status: AI-generated
- Last Updated: 17/01/2025 by AI
- Certification: 0/2 reviews


