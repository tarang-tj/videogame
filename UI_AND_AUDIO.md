# UI, Audio, and Juice (Editor Checklist)

Hook these up in the Unreal Editor after opening the project.

## UMG HUD

1. Create **Widget Blueprint** `Content/UI/WBP_HUD` (parent: `User Widget`).
2. Add **Progress Bar** (bind to `HealthComponent` → `GetHealth` / `GetMaxHealth` via `PlayerCharacter` or a small Blueprint interface).
3. Add **Text** for fragment count, currency, and level (`GetCollectibleCount`, `ProgressionComponent`).
4. Open **Blueprint** for `WebAdventureHUD` (subclass of `AWebAdventureHUD` if you need overrides) or set the **HUD Class** on your Game Mode to `AWebAdventureHUD` and assign **HUD Widget Class** → `WBP_HUD`.

## Pause menu

- Add **Input Action** `Pause` → open `WBP_Pause` with **Set Input Mode UI Only** / **Game And UI** as appropriate.
- Buttons: Resume, Quit (console command `quit`).

## Audio

- Import **Sound Wave** assets under `Content/Audio/`.
- Add **Audio Component** to `PlayerCharacter` or use **2D/3D** cues for footsteps, attack whoosh, hit, pickup, UI click.
- Add **Sound Cue** for music; use **Level Blueprint** or **Ambient Actor** for area music.

## Juice

- **Camera shake**: use `CameraShake` Blueprint on hit; trigger from `EnemyCharacter` damage or player attack.
- **Particles**: spawn at pickup location and on enemy death.
- **Post-process**: add **Post Process Volume** (infinite) with mild bloom/vignette.
