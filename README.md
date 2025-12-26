[![GitHub Release](https://img.shields.io/github/v/release/YOURNAME/GMX?include_prereleases&sort=date&display_name=tag&style=flat&label=Release)](https://github.com/ahmed007boss/GeneralsGameCode/releases)
![GitHub milestone details](https://img.shields.io/github/milestones/progress-percent/YOURNAME/GMX/1)
![GitHub milestone details](https://img.shields.io/github/milestones/progress-percent/YOURNAME/GMX/2)

[![GitHub issues by-label](https://img.shields.io/github/issues/YOURNAME/GMX/bug?style=flat&label=Bug%20Issues&labelColor=%23c4c4c4&color=%23424242)](https://github.com/ahmed007boss/GeneralsGameCode/issues?q=label%3ABug)
[![GitHub issues by-label](https://img.shields.io/github/issues/YOURNAME/GMX/enhancement?style=flat&label=Enhancement%20Issues&labelColor=%23c4c4c4&color=%23424242)](https://github.com/ahmed007boss/GeneralsGameCode/issues?q=label%3AEnhancement)

---

# Welcome to the GMX Project  

**GMX (Generals Modding eXtended)** is a community-driven extension of the open-source *Command & Conquer: Generals – Zero Hour* codebase.  

GMX is built directly on top of [GeneralsGameCode](https://github.com/TheSuperHackers/GeneralsGameCode), maintained by *TheSuperHackers* and community contributors.  

This project will:  
- ✅ **Inherit all bug fixes and enhancements** from the community project.  
- ✅ **Extend modding support** beyond INI editing, providing APIs and frameworks for advanced mods.  
- ✅ **Remain compatible** with *Generals: Zero Hour* while enabling brand-new gameplay systems.  

⚡ GMX is not a fork that drifts away—it is an **expansion layer** that tracks upstream fixes and improvements.  

---

## Project Overview  

The community project focuses on **stability, modernization, and bug fixing**.  
GMX builds on that foundation by adding a **new layer for modding and content creation**.  

### Key Features  
- **Custom Gameplay Systems** → damage types, weather effects, advanced AI, special effects.  
- **Improved Tooling** → better error reporting, debugging tools, hot-reload for modders.  
- **Asset Expansion** → support for new particle effects, shaders, audio, and UI integration.  
- **Upstream Sync** → every release includes the latest GeneralsGameCode fixes.  

---

## Versioning  

GMX follows **semantic versioning** (`MAJOR.MINOR.PATCH`):  

- **Patch releases** (`1.04.1`) → Upstream fixes only, no breaking changes.  
- **Minor releases** (`1.3.0`) → New modding features, backwards compatible.  
- **Major releases** (`2.0.0`) → Breaking changes or when retail compatibility is dropped.  

Each GMX release notes the **upstream sync point** (e.g., "Includes GeneralsGameCode v0.9.4").  

---

### Dependency management

The repository uses a vcpkg manifest (`vcpkg.json`) paired with a lockfile (`vcpkg-lock.json`). When you add or upgrade
dependencies, run `vcpkg install --x-manifest-root . --triplet <triplet>` with `VCPKG_FEATURE_FLAGS=versions` so the
lockfile picks up the new versions and include the updated lockfile in your change. GitHub Actions consumes these ports
through `VCPKG_BINARY_SOURCES=clear;files,<workspace>/vcpkg-bincache,readwrite` (paired with an `actions/cache` entry for
that folder), so the first CI build warms the cache and subsequent builds pull prebuilt binaries instead of
re-compiling everything.

---

## Reporting Bugs

GMX only tracks **bugs related to modding features, APIs, and tools**.  

- 🐞 **Game Bugs / Engine Issues** → Report to [GeneralsGameCode Issues](https://github.com/TheSuperHackers/GeneralsGameCode/issues).  
- 🛠️ **GMX-Specific Bugs** (extended APIs, modding tools, new systems) → Report in [GMX Issues](https://github.com/ahmed007boss/GeneralsGameCode/issues).  

When reporting, please include:  
- GMX version (from release tag).  
- Steps to reproduce.  
- Logs, crash dumps, or mod files if relevant.  

---

## Feature Requests  

GMX’s mission is to **extend modding support**.  
Feature requests must be **focused on modder use-cases**.  

### ✅ Examples of Accepted Requests  
- APIs for unit logic, projectiles, damage, or effects.  
- Extensions to INI (new fields, parameters, object properties).  
- Modder tools (logging, debugging, hot-reload).  
- Asset pipeline improvements (particles, shaders, audio hooks).  
- Exporters and editors for modding workflows.  

### ❌ Out of Scope  
- Engine stability or vanilla bug fixes (→ report upstream).  
- Gameplay balance or campaign changes.  
- Requests involving copyrighted EA/third-party assets.  

👉 Submit requests using the [Feature Request Template](.github/ISSUE_TEMPLATE/feature_request.md).  

---

## Contributing  

Ways you can contribute:  
- **Bug Reports** → Only for GMX-specific modding issues.  
- **Feature Requests** → Must be modding-focused (see above).  
- **Code Contributions** → PRs adding APIs, tools, or modding features.  
- **Docs & Wiki** → Help document new APIs and modding workflows.  
- **Testing & Feedback** → Try new features, provide modder feedback.  

Before contributing:  
- Ask: *Does this belong in GMX (modding) or GeneralsGameCode (engine fix)?*  
- Keep GMX extensions modular and documented.  
- Follow upstream coding style and standards.  

---

## Running the Game  

You need the original *Command & Conquer: Generals and Zero Hour*.  
- Available in [Command & Conquer The Ultimate Collection](https://store.steampowered.com/bundle/39394).  
- Download the latest GMX build from [Releases](https://github.com/ahmed007boss/GeneralsGameCode/releases).  
- Setup instructions are in the [Wiki](https://github.com/ahmed007boss/GeneralsGameCode/wiki).  

---

## Building GMX  

GMX uses the same toolchain as GeneralsGameCode.  

- **Supported:** Visual Studio 2022, Docker, CLion.  
- **Legacy:** Visual Studio 6 (for compatibility).  

Full instructions in the [Build Wiki](https://github.com/ahmed007boss/GeneralsGameCode/wiki/build_guides).  

---

## Credits  

- **Upstream Project:** [GeneralsGameCode](https://github.com/TheSuperHackers/GeneralsGameCode), maintained by *TheSuperHackers* and contributors.  
- **GMX Development:** Extends their work to build a stronger modding framework for the community.  

🙏 Thanks to the entire community keeping *Generals & Zero Hour* alive!  

---

## License & Disclaimer  

This project is licensed under the **GPL-3.0 License**, the same as GeneralsGameCode.  
- You may freely use, modify, and distribute under this license.  
- See [LICENSE.md](LICENSE.md) for details.  

⚠️ EA has not endorsed and does not support this product.  
All trademarks are property of their respective owners.  
