# CharacterDeviceDriver

Pre-Requisites

  - Any Linux platform
  
  - SuperUser Permissions

Functions/Features

  - Creates a Character Device Driver which can contain upto 256 characters although this **can be changed** easily according to user requirements!
  
  - You **don't have to worry** about allocating Major and Minor numbers, this program finds available numbers and creates driver.
  
Installation
  
  - Open terminal, navigate to the directory wherein all files are saved and run these commands.
  
  - "chmod +x combine"
  
How to Use?

  - Open terminal, navigate to the directory wherein all files are saved and run these commands.
  
  - "./combine" to start the device driver
  
  - "./user_read" to read from the device file
  
  - "./user_write" to write something to device file
  
  - "./remove" to remove cache generated and the driver from kernel space.
  
  - "tail -f /var/log/syslog" for debugging. (Must be run in a new terminal)
  
  - For more information on checkout the manual file!
  
  - Now you can store strings in RAM until you want.
