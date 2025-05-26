# Learning to run

The point of this project is that I want to learn re-enforcement learning. There is a greater, more granular goal of making a fun game. I aim to complete the whole project, but honestly I am already moderately happy for having completed the phase 0. Let's see how this goes, wish me luck.  

## The game

In the game, the player will train an agent, that is tasked to navigating a set of 2D environments. First, the player has to move the agent manually, which will be difficult and burdensome. It will grant the user resources, which allow them to evolve their agent in different ways.

### Building a better agent

Ideas for actions user can take
 - [ ] Add bodyparts to agent
 - [ ] Remove bodyparts
 - [ ] Research new
    - [ ] bodyparts
        - [ ] sensors
        - [ ] brain
        - [ ] wheel
        - [ ] spring
    - [ ] sets of constraints for bodyparts
    - [ ] training algorithms
    - [ ] training heuristics
 - [ ] Train agent with algorithm x in environment y

Note: the idea is that agent will be trained locally using local computational resources. 

### Environments

There could be a set of environments, with varying level of difficulty. The easiest environment would be a completely level plane. Successfully traversing the harder environments will give the player more resources. Some of the harder environments could be randomly generated, which might make the training process more difficult. 

### Winning

Something like traversing distance d in the hardest environment could result in a victory screen. Ofc the user can after that continue to improve the agent.


## Use of AI

The point of this project is for me to learn, so I will avoid writing code with AI tools. I often use Claude to provide me with generic examples, when I find the examples in Box2D etc. documentation inadequate. I also might generate the code for some stuff like menus using AI, if I deem coding such things is uninteresting. 

## TODO

Phase 0: Create the environment

 - [x] Add Box2D and SFML as submodules
 - [x] Create a simulation loop
 - [x] Link graphics to simulation
 - [x] Add objects
    - [x] Box
    - [x] Circle
    - [x] Capsule
 - [x] Link objects with joints
 - [x] Build a prototype agent

Phase 1: Toward re-enforcement learning

 - [ ] Create basic agents
    - [x] Dog
    - [ ] Car
 - [ ] Follow agent with camera
 - [ ] Dynamic environment generation based on agent movement
 - [ ] Implement a simple re-enforcement learning algo
    - [ ] Which algorithm?
    - [ ] Probably requires adding functionalities to agents
 - [ ] Add sensors to an agent
 - [ ] Research and implement more algorithms
    - [ ] ???
    - [ ] ???

Phase 2: Modular blocks  

At this point we shown that the re-enforcement learning works and the agents can learn to move. The big challenge will be building "the agent editor". It needs to provide the user with intuitive controls for editing their agent according to the section "Building a better agent". 


Phase 3: Polish  

Add navigation menus, maybe improve the art, think about how will other people run this on their computers. Sounds would ofc be nice to have. 





