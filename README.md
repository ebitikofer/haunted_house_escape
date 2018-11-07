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
- [ ] lighting for every object?
- [ ] light effects on player
- [ ] player representation
- [ ] hallucinations
- [ ] 2D overlay
- [ ] start screen
  EASY:
- [ ] proper windows
- [ ] light switch and fire
- [ ] agency movement
- [ ] pickups and functionality
- [ ] using objects in proximity
- [ ] ending
  TEDIOUS:
- [ ] more lights
- [ ] enemy collision with walls
- [ ] ...everything else
