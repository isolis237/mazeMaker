# mazeMaker
<b> Description </b>
Creates random mazes and solves them using disjoint sets datastructure and BFS algorithm

<b> How to Run </b>
After cloning repo,
1) in a terminal run <i> make </i>
2) run newly made file ./mazes

This will generate two mazes a small one 10x10 and a larger one 750x750 and output both the empty maze and the solved maze.
- smallMaze.png is the small randomly generated maze unsolved
- smallMaze_solved.png is the small maze solved
- same thing with bigMaze


In main.cpp the size of the maze can be changed by changing the width and height in the call to makeMaze(width,height)


Example Outputs (small random maze solved and unsolved + big maze solved):
<img width="112" alt="Screen Shot 2021-12-29 at 9 40 25 PM" src="https://user-images.githubusercontent.com/67722662/147719915-c494a598-7403-4e1a-b222-eb2096bd1a06.png">
<img width="122" alt="Screen Shot 2021-12-29 at 9 40 32 PM" src="https://user-images.githubusercontent.com/67722662/147719918-82d0d109-708e-4d0c-bb14-7ed014314418.png">
<img width="1003" alt="Screen Shot 2021-12-29 at 9 40 48 PM" src="https://user-images.githubusercontent.com/67722662/147719922-cadb4eec-6984-4e71-8b8a-ab8c233457da.png">
