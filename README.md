# Chess Game with AI (Alpha-Beta Pruning)

This is a command-line Chess Game implemented in C++. The game features an AI opponent that uses the Alpha-Beta Pruning algorithm to evaluate board positions and make moves. The project aims to demonstrate the implementation of the Alpha-Beta Pruning algorithm in a game of chess.

## Features

- Play against an AI opponent powered by the Alpha-Beta Pruning algorithm
- Visualize the chess board and game state in the terminal
- Move validation and legal move generation for all pieces
- Check for checkmate and stalemate conditions
- Basic board evaluation function for AI decision-making
- Transposition table to improve AI performance

## Requirements

- C++ compiler supporting C++11 or later
- Make utility for building the project

## Installation

1. Clone the repository:

```
git clone https://github.com/your-username/chess-game-ai.git
```

2. Navigate to the project directory:

```
cd chess-game-ai
```

3. Build the project using Make:

```
make
```

This will compile the source code and generate the executable `chess`.

## Usage

Run the compiled executable:

```
./chess
```

The game will start, and you can follow the on-screen instructions to make moves. The AI opponent will automatically make its moves using the Alpha-Beta Pruning algorithm.

## Game Flow

1. The game starts with the initial chess board configuration.
2. You will be prompted to enter your move in algebraic notation (e.g., e2e4 to move the white pawn from e2 to e4).
3. After your move, the AI opponent will calculate its best move using the Alpha-Beta Pruning algorithm.
4. The game continues until checkmate, stalemate, or a draw condition is reached.
5. The final result (win, loss, or draw) will be displayed.

## AI Implementation

The AI player uses the Alpha-Beta Pruning algorithm to evaluate board positions and make moves. The algorithm explores the game tree by recursively evaluating positions and pruning unnecessary branches based on the minimax principle.

The AI's decision-making is guided by a board evaluation function that assigns scores to different board configurations. The evaluation function considers factors like material balance, piece positioning, and king safety.

A transposition table is used to store and retrieve previously evaluated board positions, improving the AI's performance by avoiding redundant calculations.

## Contributing

Contributions to this project are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

