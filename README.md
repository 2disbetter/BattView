BattView is intended to allow quick review of your battery level (percentage) and current status, because the status bar (either in a traditional DE like Gnome or KDE, or in a tiling manager using waybar, for example) is not present. This uses QT and allows the use of a keyboard combo to show the prompt. Its purpose is simply to allow the quick review of your current battery status. 

You can move the binary to /usr/local/bin/ and give it permissions to run, then you would set a keycombo in your hyprland.conf similar to this: 
```
bind = SUPER, B, exec, BattView
```
<img width="1920" height="1200" alt="image" src="https://github.com/user-attachments/assets/41d82809-9e62-4565-84b9-92f0bc1ac027" />
This is release 1.1.

Release 1.2 adds CPU temp and fan RPMs as well. Currently this is specifically for the Framework 12. It might work on other machines that are compatible with ectool. If not you will need to modify the source code to reflect the correct naming schemes for your hardware. 

<img width="307" height="171" alt="image" src="https://github.com/user-attachments/assets/9a3a7a77-8259-47f2-91f3-6eae8d37c8f1" />

Note: For version 1.2 you will need the ectool from Framework, and you will need to set it with chmod u+s. If you are not comfortable with this, then please stick with version 1.1 which has no ectool requirement. 

Version 1.1 is still available here as the standard stable release. If you have a Framework 12 and would like this additional information, 1.2 is for you. 
