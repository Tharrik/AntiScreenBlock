# What is AntiScreenBlock
AntiScreenBlock (or ASB for short) is a program designed to run in the background of Windows to avoid inactivity states. This allows the user to do something else while the machine is running long tasks (downloads, renders, compiling, etc.). Programs like Discord, Microsoft Teams or Skype won't go into inactive mode and Windows won't go to the block screen.

# Q&A
### How does ASB work?
AntiScreenBlock just moves the mouse cursor at a fixed rate to make Windows think that the user is active.

### I could just configure Windows and my apps so they don't go to inactive mode, right?
Yeah, of course, but ASB is not designed to personal use in a personal computer that can be configured to avoid inactivity states. ASB is **designed for work stations** that are configured by the IT department of companies and organizations and can't be configured by the user.

### So, is ASB a program to avoid being catch when I'm not doing my job?
You could use it for that, but it isn't its main focus and **won't fool most activity and monitoring trackers**. ASB it's designed to use while long processing programs (downloads, render, compiling, debugging, etc.) are running without the user's supervision. This prevents Windows from blocking the user's session, avoiding possible errors or failures.

### Do I need to pay to use ASB?
No, ASB is **free to use**. If you want to **contribute to its development**, you can donate [here](https://www.paypal.com/donate/?hosted_button_id=5WJBQY7JRR4LW)

### Will ASB be very heavy on my CPU?
No, the performance issues have been solved. ASB when from using a ~25% of CPU to an average of 0,1% on the system tested.

### Is ASB still in development?
ASB is currently in open beta and in active development.

### Can I use the source code of ASB to make my own software?
Yes, you can. ASB uses a [MIT License](https://opensource.org/license/mit/). You only need to **include the copyright notice** in your project.

### Is ASB safe to use?
ASB is **open source** so you can check that there isn't any malicious code like cryptominers, keyloggers, trojans, backdoors, etc.

### I downloaded ASB from the Internet. Is it safe to use?
ASB is not officially to download in the Internet. If you downloaded it anywhere else than this repository, is most probably **not safe to use**.

### Will ASB run on my computer?
ASB is developed for Windows. It has been **tested on Windows 10**, so it should work on Windows 11. Previous versions of Windows have not been tested.

# How to use ASB
To use ASB just download this repository, compile it and run it.

## Program arguments
You can modify ASB behaviour using execution arguments. NOTE: you can use both '-' and '/' preceding the argument symbols.

### Time
Time between mouse movement actions in milliseconds. By default, this value is 120000 (2 minutes).

~~~
asb.exe -t 60000
Time between actions: 60000 milliseconds
~~~

### Mouse displacement
Vector of displacement of the mouse. By default, this value is {1,0}.

~~~
asb.exe -dx 0 -dy -1
Mouse displacement: {0,-1}
~~~

### Show information
Show an information window. **This feature is currently in development and isn't finished**. By default, this window is hidden.

~~~
asb.exe -s
Show information window
~~~

### FPS
Frames per second target for the information window. By default, this value is 30.

~~~
asb.exe -fps 60
FPS target: 60
~~~

# Development roadmap
## Implemented features
- Avoids windows from going to sleep or blocking the user's session.
- Very low CPU consumption
- Configurable behaviour through program arguments

## Planed features
- The application runs in the system tray and doesn't show in the task bar
- The system tray icon has a contextual menu with options:
    - Show/hide info
    - Exit
