## WebAdventure – Unreal Engine 5 3D Game

This folder contains the source code and design docs for **WebAdventure**, an ambitious 3D game built with **Unreal Engine 5 (C++)**, targeting desktop first and web delivery later via **Pixel Streaming**.

This repo is meant to sit **inside an Unreal project**. You will either:

- Create the Unreal project in this directory, or
- Create it elsewhere and then move or merge the generated `Source/` and `.uproject` into here.

> The files here follow standard Unreal 5 C++ conventions, so they will integrate cleanly once you create a matching Unreal project named `WebAdventure`.

---

## 1. Engine & Tooling Setup (macOS)

1. **Install Unreal Engine 5.x**
   - Install the **Epic Games Launcher**.
   - From the *Unreal Engine* tab, install the latest stable **UE 5.x**.
2. **Install C++ toolchain**
   - Install **Xcode** from the Mac App Store (this provides the compilers Unreal uses on macOS).
   - Open Xcode once so it can install command line tools.
3. **Verify C++ project creation**
   - In the Epic Games Launcher → Unreal Engine → *Launch*.
   - Click **Games → Next → Third Person (or Blank)**.
   - Set **Project Type = C++**, **Starter Content = On**.
   - Name it exactly **`WebAdventure`** and set the folder to this directory (`Desktop/Video Game`).
   - Click **Create** and wait for Unreal to generate and open the C++ project.

Once Unreal has generated the project, you will see:

- `WebAdventure.uproject`
- `Source/WebAdventure/` (and potentially `Source/WebAdventureEditor/`)
- `Content/` and other standard Unreal directories

The C++ files provided in this repo are designed to **replace or extend** the generated defaults.

---

## 2. Repository & Ignore Conventions

If you git-init this project, use an Unreal-focused `.gitignore` and **do not** commit derived artifacts.

Recommended to ignore:

- `Binaries/`
- `DerivedDataCache/`
- `Intermediate/`
- `Saved/`
- `*.sln`, `.vs/`, `.idea/` (depending on IDE)
- `*.opensdf`, `*.sdf`, `*.VC.db`

You can safely commit:

- `.uproject`
- `Source/` (C++ code)
- `Config/`
- `Content/` (assets, Blueprints, maps)
- `Plugins/` (if any)

---

## 3. Project Structure Overview

Once Unreal has created the project, the structure will look like:

- `WebAdventure.uproject`
- `Source/`
  - `WebAdventure/`
    - `WebAdventure.Build.cs`
    - `WebAdventureGameModeBase.h/.cpp`
    - `PlayerCharacter.h/.cpp`
    - `EnemyCharacter.h/.cpp`
    - `Collectible.h/.cpp`
    - `HealthComponent.h/.cpp`
    - `Interactable.h`
  - `WebAdventureEditor/` (optional, if you add editor modules)
- `Config/`
- `Content/`
  - `Maps/`
  - `Characters/`
  - `Enemies/`
  - `Props/`
  - `UI/`
  - `Blueprints/`
  - `Audio/`
  - `Materials/`
  - `FX/`

The classes in `Source/WebAdventure/` implement:

- A base **player character** with third-person camera, health, and basic movement.
- A base **enemy character**.
- A simple **health component** and **damage system**.
- A **collectible** actor to support the core loop.
- An **interaction interface** for doors, chests, levers, etc.

---

## 4. Input Mappings (to set in Unreal Editor)

In **Edit → Project Settings → Input** (or **Enhanced Input** mappings), configure:

- **Axis mappings**
  - `MoveForward`: `W` = +1, `S` = -1, `Gamepad Left Y`
  - `MoveRight`: `D` = +1, `A` = -1, `Gamepad Left X`
  - `LookUp`: Mouse Y, Gamepad Right Y
  - `Turn`: Mouse X, Gamepad Right X
- **Action mappings**
  - `Jump`: Spacebar, Gamepad Face Button Bottom
  - `Sprint`: Left Shift
  - `Attack`: Left Mouse Button / Gamepad Right Trigger
  - `Interact`: `E`
  - `Pause`: `Esc` / Start

These names are referenced from the C++ character classes.

---

## 5. High-Level Design Docs

Additional design-focused docs live alongside the code:

- `DESIGN_CORE_LOOP.md`: Defines the main game loop, level structure, and win/fail conditions.
- `WEB_DEPLOYMENT.md`: Describes the Unreal Pixel Streaming–based web delivery and deployment pipeline.

Read those next to understand gameplay and deployment goals.

---

## 6. Git repository

This project folder is a **standalone Git repo** for WebAdventure (not your home directory).

- **Clone / remote**: add a remote on GitHub, GitLab, or Bitbucket and push:

  ```bash
  cd "/Users/tarangjammalamadaka/Desktop/Video Game"
  git remote add origin <your-repo-url>
  git branch -M main
  git push -u origin main
  ```

- **What to commit**: `.uproject`, `Source/`, `Config/` (when present), `Content/`, `*.md`, `.gitignore`.
- **Do not commit**: `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/` (already listed in `.gitignore`).

If Unreal regenerates solution files locally, they stay ignored unless you choose to commit them for a team workflow.

---

## 7. Next Steps

1. Open `WebAdventure.uproject` in Unreal Engine (or create a new C++ project named `WebAdventure` here and merge these `Source/` files).
2. If the engine version differs, right-click the `.uproject` → **Switch Unreal Engine version** as needed.
3. Configure **Project Settings → Input** (or Enhanced Input) using the action names in this README.
4. Press **Play** to test movement, **Attack** (trace vs. `AEnemyCharacter`), **Interact** (trace vs. `ADoorActor`), and pickups (`ACollectible`).
5. Build levels and UI using `DESIGN_CORE_LOOP.md`, `WEB_DEPLOYMENT.md`, and `UI_AND_AUDIO.md`.

