# having fun building a tic tac toe

## Why

Friday morning, C lab, I've already finished the work of all the labs, and the
last exercise asked to build a tic-tac-toe.

I am interest in learning Reinforcement Learning techniques so I was like, yeah
let's build a RL algo to learn how to beat this game.

So I started reading the [Sutton & Barto's book](http://incompleteideas.net/sutton/book/bookdraft2017nov5.pdf)
but my professor suggested me to start with the minimax algo, because RL is
overkill for the ttt.

So I am just going to use different techniques to solve this problem. I am just
trying to learn stuff.

## Minimax

Minimax 1.0.0 is done and works fine.
Minimax.c implements the minimax algorithm, you can try it, but you will never
be able to win.

### alpha-beta

TODO : implement alpha-beta to optimize the algorithm.

## Temporal difference learning

Temporal difference seems to be the very first, basic, RL algorithm. This 
method cares about :

* the different States (S)
* the rewards (R)
* the value & value function (V)
* the actions (A)

The reward bring an immediate feedback on the environment state, did you lose ?
You get -10 points. Did you win ? you get 10 points. No one win : 0 points.
The game isn't over ? you get no point ?

The value is the probability of winning. 1 you win, 0 you lose, 0.319873 : it doesn't look good for you. We approximate state values by updating values of
visited states after each training game :

	V(s) <- V(s) + alpha.[V(s')-V(s)]

where

* `s` is the current state
* `s'` is the next state
* `V(s)` is the state value for s
* `alpha` is the learning rate varying within ]0,1]

At the beginning of the game, for all states, V(s) = 0.5.

What about the policy ?

The policy choose the move with the best value 90% of the time. It picks a
ramdom/exploratory move the remaining 10%.


## Bibliography

* <https://neverstopbuilding-dropblog.herokuapp.com/minimax>
* <http://incompleteideas.net/sutton/book/bookdraft2017nov5.pdf>
* <https://gist.github.com/MatthewSteel/3158579>
* <https://youtu.be/STjW3eH0Cik>
* <https://medium.com/@shiyan/get-a-taste-of-reinforcement-learning-implement-a-tic-tac-toe-agent-deda5617b2e4>
* <https://www.intelnervana.com/demystifying-deep-reinforcement-learning/>
* <https://en.wikipedia.org/wiki/Temporal_difference_learning>
* <http://www.cs.dartmouth.edu/~lorenzo/teaching/cs134/Archive/Spring2009/final/PengTao/final_report.pdf>