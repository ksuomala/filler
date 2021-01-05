
<html>
<h1>Filler</h1>
<p>This is a Hive Helsinki project I was working on in the end of 2020. I created an algorithm that plays the Filler game, and a visualizer for the game.</p>
<br />
<br />

<h2>What is Filler?</h2>
<p>Filler is a (very famous) game that is played by two players on an arbitrarily sized rectangular board. The goal of the game is (to humiliate your opponent by) placing more pieces on the board than the other player. The game was provided as a Ruby script called filler_vm. In the beginning of the game the VM creates a board of an arbitrary size. On each turn it generates a randomly sized and shaped token. My task is to create a player algorithm written in C. On each turn the Filler VM writes the board(with all the previously placed pieces on it), and a random token(to be placed on the board) to the players stdin. To place the token on the board the player should write the coordinates on the standard output in the form of: Y X\n. 

As a bonus I created a visualizer using the SDL graphics library.</p>
</html>

<html><h1>The Algorithm</h1></html>
      My filler algorithm places the piece as close to the enemy as possible. To calculate the distance from the other player I created a heatmap, that saves the       distance to the nearerst enemy piece for each coordinate.
      
![heatmap](https://github.com/ksuomala/filler/blob/master/images/heatmap.png)

Pieces are placed as close to the opponent as possible, surrounding the opponent and making it impossible for them to expand. Here is one game played against a fellow students algorithm.

![heatmap_video](https://github.com/ksuomala/filler/blob/master/images/filler_test.mp4)
