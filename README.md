# minimaxmoe 🕹️🤖

> **"Why study game trees for an AI exam when you can weaponize them in 40 minutes instead?"**

`minimaxmoe` is an unbeatable Tic-Tac-Toe agent written in pure **C** with **Raylib**, powered by the classic **Minimax** algorithm.

The name? A phonetic collision of **Minimax** and **Tic-Tac-Toe** (with just enough existential dread sprinkled in)

---

## 📖 The Origin Story

It was late. An AI examination was looming.

Instead of reading theory like a responsible student, boredom took over. Naturally, the only sensible response was productive procrastination:

1. Open Vim
2. Speedrun an unbeatable AI engine in C in 40 minutes.

---

## 🧠 How It Works

Under the hood in [`ai.c`](ai.c), the engine uses standard recursive **Minimax** to explore every possible move sequence down to terminal states:

```
          [ You make a move ]
                  │
                  ▼
         [ Minimax evaluates ]
        ╱         │         ╲
  Loss (-10)   Draw (0)   Win (+10)
        ╲         │         ╱
         "Nice try, human."
```

Because Tic-Tac-Toe has a total game-tree complexity of only ~255,168 possible leaf nodes (and even fewer reachable distinct states), the AI calculates the optimal outcome instantaneously.

### Expected Outcomes
| Outcome | Probability | Notes |
| :--- | :---: | :--- |
| **Draw** | ~50% | If you play with zero mistakes. |
| **Defeat** | ~50% | You blinked, misplaced an X, and got fork-trapped. |
| **Victory** | 0% | Physically impossible unless you segfault the binary or get kernel access |

---

## 🎮 Controls & Gameplay

- **Left Mouse Button**: Place your mark.
- **`R`**: Rage-reset the board after walking directly into a trap.
- **Close Window**: Accept defeat and go study.

---

## 🚀 Building & Running

### Prerequisites

You'll need `clang` / `gcc` and [Raylib](https://www.raylib.com/).

On macOS (via Homebrew):
```bash
brew install raylib just
```

### Run with `just`

```bash
just run
```

### Or manually compile:

```bash
cc -o main main.c ai.c engine.c \
   -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib \
   -framework CoreVideo -framework IOKit -framework Cocoa \
   -framework GLUT -framework OpenGL

./main
```

---

## ⚖️ License & Disclaimer

Built in 40 minutes of intense pre-exam procrastination. If you lose to this bot, do not punch your monitor—simply blame graph theory.
