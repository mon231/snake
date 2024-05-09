# snake
Implementation of the Snake game, with an AI player bot.

## Game Definitions
The game takes place on a rectangle (screen rate of 4:3, thus exists `x` where `width=4x` and `height=3x`) with configurable `x` param,
The snake has head only when it is spawned, and is spawned anywhere within the rectangle.
In each frame (except the one where the snake fills the whole screen), there is one (and only one) apple in the screen.
When an apple is eaten by the snake, his size grows in one "pixel".
When the snake head collides itself or the screen boundaries, the game is lost.
When the snake fills the whole screen, the game is won.

When lost, the score is the amount of apples the snake ate during the game.
When won, the score is 1.2 * the amount of apples the snake ate during the game.

## Game GOAL
Create an implementation of the Sname game, with support in headless mode playing,
And a super high FPS rate, in order to have a fast way to train our AI model.
The AI player-bot might be implemented using genetic algorithm.

## Player Bot GOAL
We'd like to develop a bot that could win the game.
At first we'll develop the game, then a minimal player bot interface,
Then train an AI model and optimize it.
