Instructions:

    sudo apt-get update
    sudo apt-get install git
    sudo apt-get install freeglut3-dev
    sudo apt-get install libglew-dev
    git clone https://github.com/ebitikofer/opengl_primative_engine.git
    cd opengl_primative_engine
    make shader
    make
    ./game

CAMERA CONTROLS:

:arrow_up:: pitch up  
:arrow_down:: pitch down  
:arrow_left:: yaw left  
:arrow_right:: yaw right  

**W**: axially forward  
**S**: axiall backward  
**A**: strafe left  
**D**: strafe right  

TODO:

   HARD:
- [x] lighting?
- [ ] light object if theres time
- [ ] material for every object?
- [ ] ~~light effects on player~~
- [ ] ^^ fake it ;) ^^
- [ ] player representation
- [x] hallucinations
- [ ] 2D overlay
- [ ] start screen

   EASY:
- [ ] light switch and fire
- [x] door rotation
- [ ] door collision
- [x] agency movement
- [x] agency chasing
- [ ] werewolf chasing
- [x] pickups
- [x] fake pickup functionality
- [x] using objects in proximity
- [ ] set all actions
- [ ] ending

   TEDIOUS:
- [x] proper windows
- [ ] more lights
- [ ] enemy collision with walls
- [ ] clean shiz up
- [ ] ...everything else
