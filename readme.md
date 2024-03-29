# [#tmmt_visual_sketch](https://www.instagram.com/explore/tags/tmmt_visual_sketch/)

[Tomoya Matsuura](https://matsuuratomoya.com)

These are the sources of my (almost) daily sketch from Sep. 2018.

## How to run

1. place this folder in openFrameworks/apps/
2. drug the folder from finder to project generator and press "update"
3. click "open in IDE"!

## Environment 

- Macbook Pro (13-inch, Mid 2012)
- High Sierra 10.13.5
- Xcode 9.4.1
- of 0.10.0 (built from git repository)
- some of works use shader with OpenGL3/GLSL 150 mode(ofLineWidth doesn't work).

*(2023-01-23) updated.*

- Macbook Pro 2019 16inch (Intel)
- macOS 12.3.1(Monteley)
- using Visual Studio Code, each space contains `.code-workspace`
- When to use `clangd` as an alternative intellisense, run `compiledb -n make` each time you add a new include file in the header to generate `compile_commands.json`.

## License

Codes are MIT Lisence. Generated images(thumbnails and videos on instagram/twitter) are [CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/2.0/).

## Contents

### grav_ball_2d

- z/x key moves the hue of color
- space to reset  background

 ![](./1_gravball_2d/thum.png)

### 2_grav_ball_3D

- mouse to move a camera(ofEasyCam)
- space to force to accelerate particles

![](./2_gravball_3d/thum.png)

### 3_automaton_study

- **it is heavy, usually up to 3fps**
- any key to reset

![3_automatonstudy](3_automatonstudy/thum.png)

### 4_bluranddistortion

- mouseX to amout of blur(also modulated by sine wave), mouseY to strength of pixel displacement
- z/x keys to global-strength of pixel displacement(displayed in top-left, recommend 10~20)

![4_bluranddistortion](4_bluranddistortion/thum.png)

### 5_6_shaderfeedback - Noise/Circle displacement by noise

- f to switch fullscreen
- r to switch to circle displacement(6)
- space to switch to noise image
- mouseX to noise strength,mouseY to amount of blur

![5_shaderfeedback](5_6_shaderfeedback/thum.png)

![thum](5_6_shaderfeedback/thum2.png)

### 7shaderfeedback2 - Rectangle displacement by noise

- almost same as above
- r to switch to rectangle

![thum](7_shaderfeedback2/thum.png)

### 8_character_spill

- you should link/copy futura.ttf from your ~/Library/fonts
- mouseX to noise strength
- f to switch fullscreen
- click to draw the characters again,space to reset the screen

![thum](8_charctersspill/thum.png)

### 9_circle_rotation

- click to reset,f to switch fullscreen(and glitch...)

(2023-01-27: glitch did not happen on newer environment, in of 0.11.2 and Macbook Pro 16inch 2019 model)

![thum](9_circlerotation/thum.png)

### 10_circle_rotation2

- click to reset,f to fullscreen
- d to debug view
- c to switch CAT mode.
- For triple-pendulum program- I modified this code. Thanks. [https://github.com/So-Takamoto/triple_pendulums](https://github.com/So-Takamoto/triple_pendulums)

![thum](10_circlerotation2/thum.png)

![cat](10_circlerotation2/cat.png)

### 11_walkingmotion_displacement

- data.h is walking motion data(in text...!) from [Zach's example](https://github.com/ofZach/SFPC_RTP_fall18/tree/master/walkingPersonExample)
- g to switch debug view
- d to switch human bone(I mistaked keys g and d, to be fixed)
- space to reset
- mouseX changes an amount of displacement

![thum](11_walkingdisplace/thum.png)

### 12_pixelsortcat

- space to reset
- up-down key to changes screen division
- z key to change sorting direction(horizontal/vertical)

### 13_cellautomatoncat

- left-right key to change images
