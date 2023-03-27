# AzerothCore Challenge Modes
Challenge Modes Module for AzerothCore

This module adds the following challenge modes:

- **Hardcore** - Players who die are permanently ghosts and can never be revived.
- **Semi-Hardcore** - Players who die lose all worn equipment and carried gold.
- **Self Crafted** - Players can only wear equipment that they have crafted.
- **Item Quality Level** - Players can only wear equipment that is of Normal or Poor quality
- **Slow XP Gain** - Players receive 0.5x the normal amount of XP.
- **Very Slow XP Gain** - Players receive 0.25x the normal amount of XP.
- **Quest XP Only** - Players can receive XP only from quests
- **Iron Man Mode** - Enforces the [Iron Man Ruleset](https://wowchallenges.com/challangeinfo/iron-man/)

Challenges can be activated per-character by interacting with the Shrine of Challenge added near the graveyard of each starting area.
Challenges can only be enabled on characters at level 1 (or level 55 for Death Knights).

Multiple challenges can be activated on a single character as long as they do not conflict, such as Hardcore and Semi-Hardcore.

Rewards for reaching level thresholds for each challenge can be added using the Config file, and can include:
- Items
- Titles
- Talent Points
- Increased XP Rate

Please note that this module uses Player Settings to store enabled challenges, so please ensure EnablePlayerSettings is set to 1 in your worldserver.conf.
