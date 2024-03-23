# 🕓🏃🏻‍♀️ Time Warp Labyrinth

### A console-based, two-player timed maze game based entirely in C

The system I've developed is an entirely console-based two-player timed maze game. Players start  
at opposite corners of the maze (one at the top left and the other near the bottom right) and must  
navigate through it to reach the centre. The first player to reach the centre wins the game while  
the other loses.

### 💻 Other features:
- [ ] array-based maze generation
- [ ] custom map creation for personalized gameplay
- [ ] obstacles introduced when time is up (as penalty)
- [ ] 3 pre-defined maps with varying difficulty levels (Easy, Medium & Hard)
- [ ] handling inputs turn-by-turn, using real-time movement with console clearing for fairness
- [ ] a theme song upon launching the program
- [ ] sound effect for when a player wins
- [ ] making sure obstacles and walls cannot be passed through to diminish cheating

### 🐛 Areas for Improvement:
*open to suggestions, <ins>especially</ins> on the following:*
- [ ] introducing actual graphics to make the game visually pleasing
- [ ] making player movement fully simultaneous instead of turn-based
- [ ] not playing music/sound effects in a separate window as it does at the moment
- [ ] minimizing the noticeable delay in the movement of player 2 as compared to player 1
- [ ] allowing the user to customize the players

### 🔧 Tweaks Needed to Run TWL:
**Edit these paths in `main()`:**  
  - [ ] Line #52: Replace `C:\\Users\\Me\\Desktop\\Time Warp Labyrinth\\twlcats.mp3`  
  with the path to the directory where you've placed the twlcats.mp3 file in.  
  For example, if you've downloaded this code and it appears in the Downloads folder,  
  you'd need to replace it with such a path: `C:\\Users\\Me\\Downloads\\Time Warp Labyrinth\\twlcats.mp3`

  &emsp;&emsp;An easier way to do this is to open Windows Explorer, navigate to the folder where  
  &emsp;&emsp;this project is located, right-click on the audio file then Select "Properties" and  
  &emsp;&emsp;copy the "Location" that shows.<br/>

  - [ ] Line #59 & #97: Replace `Program Files (x86)\\Windows Media Player\\wmplayer.exe\`  
  with the file path of your local media player. <br/><br/>

**Edit this path in `winning_message(int player)`:**  
  - [ ] Line #90: Replace `Desktop\\Time Warp Labyrinth\\won_game.wav";` with the path  
  to the directory where you've placed the won_game.wav file in. <br/><br/>  
  
  > ❗ Remember to replace the backslash `\` symbols in the copied path  
  (e.g., `C:\Users\Me\Downloads\twl.mp3`) with double backslashes `\\`  
  (e.g., `C:\\Users\\Me\\Downloads\\twl.mp3`).
