
## State space diagram

Consider the tuple `(m, c, b)` where m denotes the number of cannibals on the initial bank, c is the number of cannibals on that bank, and b is which bank the boat is in. If it is in the initial bank, the value is 1, otherwise 0. 

Therefore for our problem, the initial state is `(3, 3, 1)` and the goal state is obviously `(0, 0, 0)`. And the actions are also defined as 3-tuples as follows - 
`(⟨1,0,1⟩, ⟨2,0,1⟩, ⟨0,1,1⟩, ⟨0,2,1⟩, ⟨1,1,1⟩)`. The actions are performed by adding and subtracting the actions tuples from each state alternatively. We can check for valid states by ensuring that there are more missionaries than cannibals on both sides. Ignoring the repeated states and the invalid states, the state space diagram is as follows - 

![[New Doc 01-27-2024 23.44.jpg]]

Yes we should check for repeated states in out program using a `explored` list. Otherwise we may fall into a loop within the space tree and there will be redundant exploration. 

I think that people find it hard to solve because it has a single goal and only 2 paths among 5 from the source node leads to a goal. Very less branches lead to a goal. Thus our human mind has trouble finding it. 

