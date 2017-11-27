# BicingBigData
Application and service for windows to show and store data from Bicing service from Barcelona

# App
The application shows statistics from all the bike stations based on a time view.

There is a SQL file that contains all the database structure to set up the environment. For testing puposes it has been added data (records from each minute from the first 7 days) for the station 1. The application creates a SQLITE database wherever the user wants. For path configuration the user can modify the global variable **PATH** in BigDataContainer.cpp.

# Service
The service is a small application that initializes a request against the Open Data server from the ViaBicing server. It makes a request every 60 seconds and stores the file.

In order to run it you can execute it as follows:
* Live execution: After compiling it, go to the executable folder and run it as administrator with the parameter **-e**.
* Background service execution: After compiling it, go to the executable folder and run it as administrator from the CMD.
  * Install it using calling the app with the parameter **-i**
  * Calling the parameter **-h** you can get help about what to do with the service in terms of execution.

