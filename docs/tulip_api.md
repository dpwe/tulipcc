# The Tulip Creative Computer API 

Here you can see the API [Tulip](../README.md) currently ships with.

# Current API

**NOTE**: Our own builds of [Tulip Desktop](tulip_desktop.md) may lag behind some of the APIs listed here. This page represents the APIs in the latest commit of our _main_ branch. If something isn't working properly, try building from scratch.

![Tulip](https://raw.githubusercontent.com/bwhitman/tulipcc/main/docs/pics/tulip4.png)

## General

[Tulip](../README.md) boots right into a Python prompt and all interaction with the system happens there. You can make your own Python programs with Tulip's built in editor and execute them, or just experiment on the Tulip REPL prompt in real time.

```python
# Interact with the filesystem.
# Supported: ls, head, cat, newfile, cp, mv, rm, pwd, cd, mkdir, rmdir
ls
mkdir('directory')
cd('directory')

# Clears the REPL screen and formatting
clear

# Run a saved Python file. Control-C stops it
cd('ex') # The ex folder has a few examples and graphics in it
execfile("parallax.py")
run('game') # Runs a package, see below

# Extract a .tar file.
tulip.tar_extract(filename)

# Create a tar file from a directory (and everything in it)
tulip.tar_create(directory)

# If you want something to run when Tulip boots, add it to boot.py
edit("boot.py")

# On Tulip CC with 16MB of flash or more, you can upgrade the firmware over-the-air over wifi
tulip.upgrade()

# Takes a screenshot and saves to disk. The screen will blank for a moment
# If no filename given will upload to imgur and return a URL (needs wifi)
tulip.screenshot("screenshot.png")
imgur_url = tulip.screenshot()

# Return the current CPU usage (% of time spent on CPU tasks like Python code, sound, some display)
# Note that Python code is bound to one core, so Python-only usage tops out at 50%.
usage = tulip.cpu() # or use tulip.cpu(1) to show more detail in a connected UART

ms = tulip.ticks_ms() # returns the milliseconds since boot, aka Arduino millis() 
```

If you have a program that relies on mulitple files (graphics, or multiple Python files) you'll want to create a Tulip Package. A package is just a folder with your files in it, like:

```
rabbit_game/
... rabbit_game.py # starts the program when imported
... extra.py # can put any other python files in here
... rabbit_pic.png
... rabbit_pic1.png
```

The main Python script must be the name of the package. This script needs to explicitly `import tulip,alles` if you are using those. Then, your users can start the package by `run('rabbit_game')`. The package will be cleaned up after when they exit. The Tulip World BBS supports uploading and downloading packages as tar files: just `world.upload('package')` or `world.download('package')`. 


## Tulip World

Still very much early days, but Tulip supports a native chat and file sharing BBS called **T U L I P ~ W O R L D** where you can hang out with other Tulip owners. You're able to pull down the latest messages and files and send messages and files yourself. 

You can call the underlying Tulip World APIs:

```python
import world
messages = world.check() # returns a list of latest messages since your last call
world.send("hello!!") # Sends a message to Tulip World

world.upload(filename) # Uploads a file to Tulip World 
world.upload(folder) # Packages a folder and uploads it to Tulip World as a package
world.download(filename) # Downloads the latest file named filename from Tulip World if it exists
world.download(package_name) # Downloads a package and extracts it

files = world.files(limit=5000) # returns the most recent N files (including versions with the same name) for selective download
world.download(files[0]) # download a specific file instead

world.ls() # lists most recent unique filenames
```

Big note: Tulip World is powered by a [Matrix](https://matrix.org) instance that I run. I can't guarantee anything about its uptime, and if there's any abuse of the system, I'll revoke the key. I'd love more help making Tulip World a more stable and fun experience for everyone. 


## The Tulip Editor

Tulip ships with a text editor, based on pico/nano. It supports syntax highlighting, search, save/save-as. 

```python
# Opens the Tulip editor to the given filename. 
# Control-X exits and prompts to save if any changes. 
# Control-O is save as
# Control-W searches
# Filename will be created on save if it doesn't exist.
edit("game.py")
```


## Input and user interface

Tulip supports USB keyboard input, joystick and touch input. (On Tulip Desktop, mouse clicks act as touch points, your computers' keyboard works, and any connected gamepad will work.) It also comes with UI elements like buttons, sliders and text entry boxes to use in your applications.

```python
# Create a callback to activate when UI elements are triggered
def ui_callback(x):
    # x is the element ID that was triggered
    print("Item %d was fired" % (x))
    if(x==1): # slider ID
        print("Slider value is now %f" % (tulip.slider(1)))
    if(x==2): # text box ID
        print("Text box now says %s" % (tulip.text(2)))

tulip.ui_callback(ui_callback)

# You can set up to 254 UI elements
tulip.ui_button(ui_element_id, "Button text", x, y, w, h, bg_pal_idx, fg_pal_idx, filled, font_number)

# Sliders -- if w > h, it will be a horizontal slider, vertical otherwise
tulip.ui_slider(ui_element_id, default_value, x, y, w, h, bar_color, handle_color)
# Gets a slider val
val = tulip.ui_slider(ui_element_id)
# Set a slider val
tulip.ui_slider(ui_element_id, val)

# This text entry box UI element is limited to 32 characters. It will wait for you to hit return to finish input
tulip.ui_text(ui_element_id, default_value, x, y, w, h, text_color, box_color, font_number)

# Checkboxes - val -- 0 is unchecked, 1 is checked
# style -- 0 is filled box, 1 is X, 2 is filled circle
tulip.ui_checkbox(ui_element_id, val, x, y, w, mark_color, box_color, style)
val = tulip.ui_checkbox(ui_element_id)
# set value
tulip.ui_checkbox(ui_element_id, val)

# No UI elements will be drawn or receive events until you set them to be active
tulip.ui_active(ui_element_id, 1)
# You can deactivate them too -- useful for many elements across pages / tabs that you "hide"
# Deactivating does not remove the graphics on the BG layer. You have to clear it yourself.
tulip.ui_active(ui_element_id, 0)

tulip.ui_del(ui_element_id) # deletes the memory for a UI component (the graphics will stay on the BG)

tulip.joy() # returns a mask of hardware joystick presses

# like joy, but also scans the arrow keys, Z, X, A, S, Q, W, enter and '
# use this in games etc so people can use either joystick or keyboard!
tulip.joyk()

# test for joystick or key presses. Try UP, DOWN, LEFT, RIGHT, X, Y, A, B, SELECT, START, R1, L1
if(tulip.joyk() & tulip.Joy.UP):
    print("up")

# Returns the current held keyboard scan codes, up to 6 and the modifier mask (ctrl, shift etc)
(modifiers, scan0, scan1... scan5) = tulip.keys()

# Gets a key ascii code
ch = tulip.key_wait() # waits for a key press 
ch = tulip.key() # returns immediately, returns -1 if nothing held

# If scanning key codes in a program, you may want to turn on "key scan" mode so that
# keys are not sent to the underlying python process 
tulip.key_scan(1)
tulip.key_scan(0) # remember to turn it back off or you won't be able to type into the REPL

# Return the last touch panel coordinates, up to 3 fingers at once
(x0, y0, x1, y1, x2, y2) = tulip.touch()

# Modify the touch screen calibration if needed (on Tulip CC only)
# Run ex/calibrate.py to determine this for your panel 
tulip.touch_delta(-20, 0) # -20 x, 0 y
tulip.touch_delta() # returns current delta

# Set up a callback to receive raw touch events. up == 1 when finger / mouse lifted up
def touch_callback(up):
    t = tulip.touch()
    print("up %d points x1 %d y1 %d" % (up, t[0], t[1]))

tulip.touch_callback(cb)

# Make your own elements on the BG with your own styling and set up your own callbacks to process them
tulip.bg_rect(200,200,50,50,23,1)
tulip.bg_touch_register(12, 200, 200, 50, 50) # 12 is an ID -- from 0-254
def bgt(id):
    print("Got a click on id %d. up was %d" % (id, tulip.bg_touch_up(id)) # bg_touch_up returns 1 for touch up

tulip.bg_touch_callback(bgt)
tulip.bg_touch_callback() # turns off
tulip.bg_touch_del(12) # removes
```


## Network

Tulip CC has the capability to connect to a Wi-Fi network, and Python's native requests library will work to access TCP and UDP. We ship a few convenience functions to grab data from URLs as well. 

```python
# Join a wifi network (not needed on Tulip Desktop)
tulip.wifi("ssid", "password")

# Get IP address or check if connected
ip_address = tulip.ip() # returns None if not connected

# Save the contents of a URL to disk (needs wifi)
# Note: the screen will blank during this operation 
bytes_read = tulip.url_save("https://url", "filename.ext")

# Get the contents of a URL to memory (needs wifi, and be careful of RAM use)
content = tulip.url_get("https://url")

# Set the time from an NTP server (needs wifi)
tulip.set_time() 
```


## Music / sound

Tulip comes with the Alles synthesizer, a very full featured 64-oscillator synth that supports FM, PCM, additive synthesis, partial synthesis, filters, and much more. See the [Alles documentation](https://github.com/bwhitman/alles/blob/main/README.md) for more information, and the [AMY Readme](https://github.com/bwhitman/alles/blob/main/README.md) for full details of the synthesizer API. Tulip's version of AMY comes with stereo sound, which you can set per oscillator with the `pan` parameter.

Once connected to Wi-Fi, Tulip can also control or respond to an [Alles mesh.](https://github.com/bwhitman/alles/blob/main/README.md) Connect any number of Alles speakers to the wifi to have instant surround sound! 

See the Alles [getting started tutorial](https://github.com/bwhitman/alles/blob/main/getting-started.md) for more information and for more music examples.

```python
alles.drums() # plays a test song
alles.volume(4) # change volume
alles.reset() # stops all music / sounds playing
alles.send(osc=0, wave=alles.ALGO, patch=4, note=45, vel=1) # plays a tone
alles.send(osc=0, pan=0) # set to the right channel
alles.send(osc=0, pan=1) # set to the left channel

# start mesh mode (control multiple speakers over wifi)
alles.mesh() # after turning on wifi
alles.send(osc=1, wave=alles.ALGO, patch=101, note=50, ratio=0.1, vel=1) # all Alles speakers in a mesh will respond
alles.send(osc=1, wave=alles.ALGO, patch=101, note=50, ratio=0.1, vel=1, client=2) # just a certain client
alles.local() # turns off mesh mode and goes back to local mode
```

Tuilp's Alles synth includes a stereo chorus unit which has a set of control parameters:

```python
alles.chorus(mix_level, max_delay_samples, lfo_freq, lfo_depth_amp, lfo_wave_shape)
```

The Roland Juno-6 stereo chorus is approximated by ```alles.chorus(level=1.0, max_delay=320, freq=0.5, amp=0.5, wave=alles.TRIANGLE)```.  The chorus can be turned on and off with ```alles.chorus(1)``` and ```alles.chorus(0)``` respectively.

It also supports reverb:

```python
alles.reverb(level, liveness, damping, xover_hz):
```

It can be turned on and off like `chorus` with `alles.reverb(1)` and `alles.reverb(0)`. 

Tulip also ships with our own [`music.py`](https://github.com/bwhitman/tulipcc/blob/main/extmod/tulip/py/music.py), which lets you create chords, progressions and scales through code:

```python
import music
chord = music.Chord("F:min7")
for i,note in enumerate(chord.midinotes()):
  alles.send(wave=alles.ALGO,osc=i*9,note=note,vel=0.25,patch=101,ratio=0.1)
```



## MIDI

Tulip supports MIDI in and out to connect to external music hardware. You can set up a python callback to respond immediately to any incoming MIDI message. You can also send messages out to MIDI out. 

On Tulip Desktop, MIDI works on macOS 11.0 (Big Sur, released 2020) and later using the "IAC" MIDI bus. This lets you send and receive MIDI with Tulip to any program running on the same computer. If you don't see "IAC" in your MIDI programs' list of MIDI ports, enable it by opening Audio MIDI Setup, then showing MIDI Studio, double click on the "IAC Driver" icon, and ensure it is set to "Device is online." At this time, MIDI will not function (but the rest of Tulip will run fine) on macOS versions before 11.0.

```python
def callback(x): # for now you have to define a callback with a dummy parameter
    m = tulip.midi_in()
    if(m[0]==144):
        print("Note on, note # %d velocity # %d" % (m[1], m[2]))

tulip.midi_callback(callback)
tulip.midi_callback() # turns off callbacks

m = tulip.midi_in() # returns bytes of the last MIDI message received
tulip.midi_out((144,60,127)) # sends a note on message
tulip.midi_out(bytes) # Can send bytes or list
```


## Graphics system

The Tulip GPU consists of 3 subsystems, in drawing order:
 * A bitmap graphics plane (BG) (default size: 2048x750), with scrolling x- and y- speed registers. Drawing shape primitives and UI elements draw to the BG.
 * A text frame buffer (TFB) that draws 8x12 fixed width text on top of the BG, with 256 colors
 * A sprite layer on top of the TFB (which is on top of the BG)

The Tulip GPU runs at a fixed FPS depending on the resolution and display clock. You can change the display clock but will limit the amount of room for sprites and text tiles per line. The default for Tulip CC is 22Mhz, which is 25FPS. This is a great balance of speed and stability for text -- the editor and REPL. If you're writing a game or animation, increase `tulip_clock` to at least 28 for 30FPS and higher. 

Some example display clocks and resolutions:

| H_RES   | V_RES   | Clock  |  FPS   | - | H_RES   | V_RES   | Clock  |  FPS   |
| ------- | ------- | ------ | ------ | --| ------- | ------- | ------ | ------ |
| 1024    | 600     | 10     | 14.98  | |512     | 600     | 10     | 19.91  |
| 1024    | 600     | 14     | 18.55  | |512     | 600     | 14     | 30.26  |
| 1024    | 600     | 18     | 23.19  | |512     | 600     | 18     | 37.82  |
| 1024    | 600     | 22     | 25.91  | |512     | 600     | 22     | 50.43  |
| 1024    | 600     | 28     | 46.37  | |512     | 600     | 28     | 75.65  |
| 1024    | 300     | 10     | 21.47  | |512     | 300     | 10     | 35.03  |
| 1024    | 300     | 14     | 34.36  | |512     | 300     | 14     | 56.05  |
| 1024    | 300     | 18     | 42.95  | |512     | 300     | 18     | 70.07  |
| 1024    | 300     | 22     | 57.26  | |512     | 300     | 22     | 93.45  |
| 1024    | 300     | 28     | 85.90  | |512     | 300     | 28     | 140.13 |

You can set a python callback for the frame done interrupt, for use in games or animations. 

```python
# returns current GPU usage computed on the last 100 frames, as a percentage of max
usage = tulip.gpu()

# returns current FPS, based on the display clock
fps = tulip.fps() 

# resets all 3 GPU systems back to their starting state, clears all BG and sprite ram and clears the TFB.
tulip.gpu_reset()

# Get or set the display clock in MHz. Current default is 18.
# Higher clocks mean smoother animations, but less time for the CPU to prepare things to draw
clock = tulip.display_clock() 
tulip.display_clock(mhz)

# You can also change the timing and resolution on the fly. 
# This is helpful for getting higher FPS with lower resolution (less pixels)
# If h_visible or v_visible is smaller than the resolution of the display, we will draw the whole h_res and v_res
# to the display but center your visible res in a window. This is helpful for the Tulip CC display which cannot 
# easily change native resolution. Your FPS will stay the same but you will have more GPU time to draw in the window.

# H_RES, V_RES, H_VISIBLE_RES, V_VISIBLE_RES should be multiples of the Tulip default font size -- 8 x 12.
(h_res, v_res, h_offscreen_px, v_offscreen_px, h_visible_res, v_visible_res,
  hsync_back_porch, hsync_front_porch, hsync_pulse_width, 
  vsync_back_porch, vsync_front_porch, vsync_pulse_width) = tulip.timing() # returns current
tulip.timing(1024, 600, 256, 150, 139, 140, 20, 20, 12, 20) # sets, will erase all display RAM

# You can set the visible window on its own with
tulip.window(1024, 240)
(w,h) = tulip.window()

# Convenience function for getting the screen width and height,
# which are just the first two values returned by tulip.timing()
(WIDTH, HEIGHT) = tulip.screen_size()

# if the display clock gets in a strange state, you can restart it by just
tulip.display_restart() # does not clear any data like gpu_reset()

# You can also manually stop and start the display. This is useful if you want to do something intensive
# that requires the resources of the GPU as well as the CPU, or want to do faster disk access
tulip.display_stop() # Tulip will still run 
tulip.display_start()

# Sets a frame callback python function to run every frame 
# See the Game class below for an easier way to make games
game_data = {"frame_count": 0, "score": 0}
def game_loop(data):
    update_inputs(data)
    check_collisions(data)
    do_animation(data)
    update_score(data) # etc
    data["frame_count"] += 1

tulip.frame_callback(game_loop, game_data) # starts calling the callback every frame
tulip.frame_callback() # disables the callback

# Sets the screen brightness, from 1-9 (9 max brightness.) 5 is default.
tulip.brightness(5)

# Show a log of the GPU usage (frames per second, time spent in GPU) to the stderr log
tulip.gpu_log_start()
tulip.gpu_log_stop()
```

## Graphics background plane

The default background plane (BG) is 2048 x 750, with the visible portion 1024x600. (You can change this with `tulip.timing()`.) Use the extra for double buffering, hardware scrolling or for storing bitmap data "offscreen" for later blitting (you can treat it as fixed bitmap RAM.) The BG is drawn first, with the TFB and sprite layers drawn on top.

Tulip uses RGB332, with 256 colors. Here's the palette: 

![tulip_pal](https://user-images.githubusercontent.com/76612/229381451-17a47367-6338-4ed2-9be3-7ec631513e6b.jpg)



```python
# Set or get a pixel on the BG
pal_idx = tulip.bg_pixel(x,y)
tulip.bg_pixel(x,y,pal_idx)  # pal_idx is 0-255 for 8-bit RGB332 mode 

# Convert between packed palette color and r,g,b
pal_idx = tulip.color(r,g,b)
(r,g,b) = tulip.rgb(pal_idx)

# Set the contents of a PNG file on the background.
# To save RAM and disk space, I recommend converting your PNG to 255 colors before moving to Tulip
# Imagemagick does this with: convert input.png -colors 255 output.png 
# Or with dithering: convert input.png -dither FloydSteinberg -colors 255 output.png
png_file_contents = open("file.png", "rb").read()
tulip.bg_png(png_file_contents, x, y)
# Or use the png filename directly 
tulip.bg_png(png_filename, x, y)

# Copy bitmap area from x,y of width,height to x1, y1
tulip.bg_blit(x,y,w,h,x1, y1)

# If you give blit an extra parameter it will not copy over alpha color (0x55), good for blending BG images
tulip.bg_blit(x,y,w,h,x1, y1, 1)

# Sets or gets a rect of the BG with bitmap data (RGB332 pal_idxes) 
tulip.bg_bitmap(x, y, w, h, bitmap) 
bitmap = tulip.bg_bitmap(x, y, w, h)

# Clear the BG with a color or default
tulip.bg_clear(pal_idx)
tulip.bg_clear() # uses default

# Drawing primitives. These all write to the BG. 
# If you want to use them for sprites, you can use bg_bitmap after drawing offscreen.
# set filled to 1 if you want the shape filled, 0 or omit otherwise
tulip.bg_line(x0,y0, x1,y1, pal_idx)
tulip.bg_bezier(x0,y0, x1,y1, x2,y2, pal_idx)
tulip.bg_circle(x,y,r, pal_idx, filled) # x and y are the center
tulip.bg_roundrect(x,y, w,h, r, pal_idx, filled)
tulip.bg_rect(x,y, w,h, pal_idx, filled)
tulip.bg_triangle(x0,y0, x1,y1, x2,y2, pal_idx, filled)
tulip.bg_fill(x,y,pal_idx) # Flood fill starting at x,y
tulip.bg_char(c, x, y, pal_idx, font_number) # proportional font, returns # of x pixels to advance for the next char
tulip.bg_str(string, x, y, pal_idx, font_number) # same as char, but with a string. x and y are the bottom left
tulip.bg_str(string, x, y, pal_idx, font_number, w, h) # Will center the text inside w,h

"""
  Set scrolling registers for the BG. 
  line is visible line number (0-599). 
  x_offset sets x position pixels to offset for that line (default is 0)
  y_offset sets y position pixels to offset for that line (default is the line number)
  x_speed is how many pixels a frame to add to x_offset (default is 0)
  y_speed is how many pixels a frame to add to y_offset (default is 0)

  For example, to scroll the BG up two pixels a frame
  for i in range(600):
    tulip.bg_scroll(i, 0, i, 0, -2) 

"""
tulip.bg_scroll(line, x_offset, y_offset, x_speed, y_speed)
tulip.bg_scroll() # resets to default

# Change individual registers
tulip.bg_scroll_x_speed(line, x_speed)
tulip.bg_scroll_y_speed(line, y_speed)
tulip.bg_scroll_x_offset(line, x_offset)
tulip.bg_scroll_y_offset(line, y_offset)

# "Swap" the visible BG with the one to its right, using the scrolling registers
# This would make 1024,0 the top left BG pixel after the first call to swap, and 0,0 after the second call to swap
tulip.bg_swap()
```

We currently ship 19 fonts with Tulip to use for the BG. Here they are:

![IMG_3339](https://user-images.githubusercontent.com/76612/229381546-46ec4c50-4c4a-4f3a-9aec-c77d439081b2.jpeg)



## Text frame buffer (TFB)

The TFB is a 128x50 character plane for fast drawing of 8x12 text glyphs. It supports 256 ANSI 
colors for foreground and background, and supports formatting. TFB is used by the text 
editor and Python REPL.

```python
# Sets a string / gets a character and/or format to the text frame buffer (TFB), 128x50 
# Format has ANSI codes for reverse (0x80), underline (0x40), flash (0x20), bold (0x10)
# fg color is palette index, 0-255, same for bg color
# Note that the REPL and editor use the TFB
tulip.tfb_str(x,y, "string", [format], [fg], [bg])
(char, format, fg, bg) = tulip.tfb_str(x,y)

# ANSI color and formatting codes have convenience functions
print(tulip.Colors.LIGHT_RED + "this is red " + tulip.Colors.GREEN + tulip.Colors.INVERSE + " and then green inverse")
# To reset ANSI formatting
print(tulip.Colors.DEFAULT)

# Tulip REPL supports ANSI 256 color modes as well
print(tulip.ansi_fg(56))

# You can also stop or start the TFB. It will maintain what is on screen in memory, and you can still read/write it
tulip.tfb_stop()
tulip.tfb_start()

# If you want to keep the existing TFB around, you can save it to a temporary buffer and recall it
# This is used in the Game() class to keep the REPL around after running a game, and the editor
tulip.tfb_save()
tulip.tfb_restore()

# You can copy what the TFB prints to your local terminal or ESP monitor for debugging
# On Tulip CC you can also type into the ESP monitor, but not yet on Tulip Desktop 
tulip.tfb_log_start() # starts copying TFB to local stderr
tulip.tfb_log_stop() # stops
```


## Sprites
You can have up to 32 sprites on screen at once, and have 32KB of bitmap data to store them in. Sprites have collision detection built in.
Sprites are drawn in order of sprite index, so sprite index 5 will draw on top of sprite index 3 if they share pixel space.

```python
# Load the data from a PNG file into sprite RAM at the memory position (0-32767). 
# Returns w, h, and number of bytes used
# Alpha is used if given
(w, h, bytes) = tulip.sprite_png(png_data, mem_pos)
(w, h, bytes) = tulip.sprite_png("filename.png", mem_pos)

# Or load sprites in from a bitmap in memory (packed pallete indexes for RGB332)
# The bitmap can be made from code you wrote, or from bg_bitmap to sample the background
# Use pal idx 0x55 to denote alpha when generating your own sprites 
bytes = tulip.sprite_bitmap(bitmap, mem_pos)

# Read bitmap data from sprite ram if you need to modify sprites or copy them to BG
bitmap = tulip.sprite_bitmap(mem_pos, length)

# "Register" a piece of sprite RAM into a sprite handle index for later use.
# Creates sprite handle #12 referencing sprite data starting at mem_pos and w,h pixels
tulip.sprite_register(12, mem_pos, w, h)  

# Turn on a sprite to draw on screen
tulip.sprite_on(12)

# And off
tulip.sprite_off(12)

# Set a sprite x and y position
tulip.sprite_move(12, x, y)

# Every frame, we update a collision list of things that collided that frame
# Collisions are evaluated every scanline (left to right and top to bottom), 
# and only on pixels that are written to the screen (not ALPHA, and must be visible)
# See world.download("collide") for an example
# Calling collisions() clears the memory of collisions we've kept up to that point. 
for c in tulip.collisions():
    (a,b) = c # a and b are sprite #s that collided. a will always < b. 
    # Check if a touch or mouse click hit a sprite by looking for sprite #31
    if(b==31): 
        print("Touch/click on sprite %d" % (a))

# Clear all sprite RAM, reset all sprite handles
tulip.sprite_clear()
```

## Convenience classes for sprites and games

We provide a few classes to make it easier to make games and work with sprites, `Sprite`, `Player`, and `Game`.

```python
def game_loop(game):
    # game.X available

# make your game a subclass of Game. This will set up the display, reset the sprites, etc, and provide a quit()
class MyGame(Game):
    def __init__(self):
        # debug=True will keep the TFB on the screen and not remove sprites/BG after finishing
        super().init(debug=False)
        # .. game setup stuff
        tulip.frame_callback(game_loop, self)

game = MyGame()
try:
    while game.run:
        time.sleep_ms(100)
except KeyboardInterrupt:
    game.quit() # will clean up 

```

You can access sprites using the `tulip_sprite_X` commands, or use our convenience `Sprite` class to manage memory and IDs for you:

```python
class Bullet(tulip.Sprite):
    def __init__(self, copy_from=None):
        super().__init__(copy_from=copy_from)
        self.load("bullet.png", 32, 32)
        b.on()
        b.move_to(20,20)

b = Bullet()
b.off() # turn off
b.on() # turns on
b.x = 1025
b.clamp() # ensure it is within screen range
b.move() # move to its most recent position
b.move_to(x,y) # sets x and y and moves

b2 = Bullet(copy_from=b) # will use the image data from b but make a new sprite handle
b2.move_to(25,25) # Can have many sprites of the same image data on screen this way
```

A `Player` class comes with a quick way to move a sprite from the joystick/keyboard:

```python
p = tulip.Player(speed=5) # 5px per movement
p.load("me.png", 32, 32)
p.joy_move() # will update the position based on the joystick
```

See `world.download('planet_boing')` for a fleshed out example of using the `Game` and `Sprite` classes.

# In progress or planned features

## Tulip Music Editor

A synth / patch editor for the AMY and Alles synth inside Tulip. [Like the YRM102.](https://www.msx.org/wiki/Yamaha_YRM-102) 

Status: building locally, will share first alpha when ready


## Scanline bresenham drawing on the sprite layer

We plan to support line drawing on the sprite layer using sprite RAM (not modifyng the BG layer) for wireframe animations.

Status: early research phase


# Can you help? 

Things we've thought of we'd love your help on:

 * Sprite editor in Tulip
 * Tile / Map editor in Tulip
 * More UI types: radio button / rich text editor with scroll bar / ~~text entry~~

Any questions? [Chat with us on our discussions page.](https://github.com/bwhitman/tulipcc/discussions)











