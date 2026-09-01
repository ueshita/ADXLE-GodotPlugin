# AGENTS.md

Repository-specific guidance for coding agents working on the ADX LE Godot plugin.

## Working agreement

- Keep changes focused on the requested behavior; avoid unrelated refactors, formatting sweeps, dependency upgrades, and asset reimports.
- Read the root documentation, Godot project files, plugin metadata, and surrounding code before editing.
- Search for nested `AGENTS.md` files. The closest file to a modified path takes precedence.
- Preserve user-authored and pre-existing working-tree changes.
- Follow existing naming, typing, formatting, signal, and error-handling conventions.

## Godot plugin conventions

- Keep the plugin self-contained under its existing `addons/` directory unless the current layout requires otherwise.
- Preserve paths and identifiers referenced by `plugin.cfg`, `.gdextension`, `.tres`, `.tscn`, autoloads, and scripts. Update every reference when renaming.
- Prefer portable `res://` paths and Godot APIs over machine-specific absolute paths.
- Separate editor-only behavior from runtime behavior. Tool scripts must not cause side effects merely by opening the project.
- Keep plugin enable/disable behavior symmetric: unregister and clean up editor UI, nodes, autoloads, signals, settings, and resources.
- Preserve Godot syntax, resource IDs, and references when directly editing serialized scenes or resources.
- Do not commit generated state such as `.godot/`, import caches, editor settings, logs, build output, or local SDK paths.
- Do not add or redistribute CRI middleware binaries, licenses, credentials, or proprietary assets unless explicitly required and permitted.

## Implementation

- Prefer the smallest maintainable change that solves the issue.
- Preserve public API compatibility unless a breaking change is explicitly requested.
- Validate values crossing the Godot/native or Godot/ADX boundary and provide actionable errors.
- Account for Godot object lifetime, signal disconnection, thread affinity, and cleanup of native/audio resources.
- Avoid blocking the main thread when the existing architecture offers an asynchronous path.
- Update documentation and examples when user-facing setup, properties, nodes, methods, signals, or configuration change.

## Validation

- Use existing documented validation scripts and commands; do not invent a parallel workflow.
- At minimum, confirm the project imports without new errors, the plugin enables successfully, and affected scripts/resources parse.
- For runtime changes, test the smallest relevant demo or scene, including a useful failure case such as a missing bank or invalid path.
- For editor changes, verify enable, reload, project reopen, and disable flows without orphaned UI or errors.
- For native/platform changes, test available affected targets and report any target that could not be tested.
- Review the final diff for import churn, generated files, absolute paths, secrets, binaries, and unrelated edits.

## Completion report

- Summarize what changed and why.
- List validation commands or manual checks and their results.
- Explicitly note untested platforms, external SDK requirements, licensing constraints, and follow-up work.
