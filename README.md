# ChamberCrawler3000 (CC3K)

**ChamberCrawler3000 (CC3K)** is a single-player, ASCII-based, turn-based dungeon crawling game built in C++. You play as a heroic adventurer battling through 5 dangerous dungeon floors, collecting treasure, using mysterious potions, and fighting randomly roaming monsters.

---

## 🚀 Features

- **Turn-based gameplay** with full control over movement and combat  
- **Character selection** with unique races and abilities (Troll, Vampire, Goblin, etc.)  
- **Randomly generated enemies**, potions, and gold per floor  
- **Custom map support** via command-line input  
- **Color-coded ASCII display** for clear in-terminal visuals  
- **Combat mechanics** with stat-based damage calculations  
- **Potion effects** (some helpful, some harmful — all unknown until used)  
- **Five-floor dungeon** with increasing difficulty  

---

## 🎮 Gameplay Overview

- `@` – You (the player character)  
- `G` (yellow) – Gold piles (collect to increase your score)  
- `P` (green) – Potions (positive or negative effects)  
- Red letters – Enemies (`O`: Orc, `E`: Elf, `M`: Merchant, `D`: Dragon, etc.)  
- `/` – Ladder to the next floor (reach it to advance)  

Enemies move **randomly**, but will attack if you’re nearby.  
You always strike first in combat, and your attacks never miss.  
The game ends when you die or complete all 5 floors.

---

## 🕹️ Controls

| Command         | Description                              |
|-----------------|------------------------------------------|
| `no`, `so`, `ea`, `we`, `ne`, `nw`, `se`, `sw` | Move in the specified direction        |
| `a<dir>`        | Attack enemy in direction `<dir>`        |
| `u<dir>`        | Use potion in direction `<dir>`          |
| `s`, `d`, `v`, `g`, `t` | Choose race: Shade, Drow, Vampire, Goblin, Troll |
| `f`             | Freeze/unfreeze enemy movement           |
| `r`             | Restart the game                         |
| `q`             | Quit the game                            |

---

## 🛠️ How to Build & Run

### Prerequisites

- A C++17-compatible compiler (e.g., `g++`)
- Unix-like terminal (with ANSI color support)

### Compile

```bash
g++ -std=c++17 -o cc3k main.cc [other .cc files]
```


Explore, survive, and reach the bottom of the dungeon.
Collect as much gold as possible and defeat enemies along the way.
Each decision matters — fight wisely, use potions carefully, and avoid being surrounded.

Good luck in the chambers of ChamberCrawler3000!
