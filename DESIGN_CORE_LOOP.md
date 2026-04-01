# WebAdventure – Core Loop & Level Blockout

## Pitch

A compact **action-adventure** slice: explore a small hub, enter **combat** and **platforming** offshoots, collect **fragments**, and spend currency in the hub to **upgrade max health**—with a clear win condition (open the exit gate).

## Core Loop

1. **Explore** the hub (`L_Hub`).
2. **Enter** side areas: `L_Arena` (enemies), `L_Cliffs` (platforming + pickups).
3. **Fight** with melee traces; enemies drop implicit progression via XP/currency hooks (extend in Blueprint).
4. **Collect** fragment pickups; count gates the exit door (`ADoorActor`).
5. **Return** to hub; optional **upgrade** via `UProgressionComponent::TryPurchaseMaxHealthUpgrade()`.
6. **Win** when the exit door opens after collecting the required fragments (e.g. 3) and interacting at the door.

## Level Blockout (editor)

Create these maps under `Content/Maps/` (names are suggestions):

| Map        | Purpose |
|-----------|---------|
| `L_Hub`   | Central plaza, NPC/upgrade placeholder, door to `L_Arena` / `L_Cliffs`, exit `ADoorActor` (requires N fragments). |
| `L_Arena` | Flat combat space, `NavMeshBoundsVolume`, 1–2 `AEnemyCharacter` placed. |
| `L_Cliffs`| Ramps/jumps, 3+ `ACollectible` placed along the path. |

**Editor steps (summary):**

- Add **Blocking Volumes** / cubes for floors and walls; use **Starter Content** materials.
- Place **Player Start** in `L_Hub`.
- Set **Game Mode Override** to `WebAdventureGameModeBase` (or project default).
- Add **Nav Mesh Bounds** in any map with AI.
- Place `ADoorActor`, set **Required Collectibles** to match your pickup count.

## Win / Fail

- **Win**: Player interacts with exit door when `GetCollectibleCount() >= RequiredCollectibles`; door opens (offset).
- **Fail** (future): player health reaches 0—`UHealthComponent` fires death; extend with respawn or game-over UI.

## Objective Text (UMG)

Bind HUD widgets to `PlayerCharacter` (health from `HealthComponent`, fragments from `GetCollectibleCount()`, currency/level from `ProgressionComponent`) for on-screen goals, e.g. “Collect 3 fragments and reach the exit.”
