BattView is intended to allow quick review of your battery level (percentage) and current status, because the status bar (either in a traditional DE like Gnome or KDE, or in a tiling manager using waybar, for example) is not present. This uses QT and allows the use of a keyboard combo to show the prompt. Its purpose is simply to allow the quick review of your current battery status. 

You can move the binary to /usr/local/bin/ and give it permissions to run, then you would set a keycombo in your hyprland.conf similar to this: 
```
bind = SUPER, B, exec, BattView
```
<img width="1920" height="1200" alt="image" src="https://github.com/user-attachments/assets/41d82809-9e62-4565-84b9-92f0bc1ac027" />
