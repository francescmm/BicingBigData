# BicingBigData
Application and service for windows to show and store data from Bicing service from Barcelona

# App

# Service
The service is a small application that initializes a request against the Open Data server from the ViaBicing server. It makes a request every 60 seconds and stores the file.

In order to run it you can execute it as follows:
* Live execution: After compiling it, go to the executable folder and run it as administrator with the parameter **-e**.
* Background service execution: After compiling it, go to the executable folder and run it as administrator from the CMD.
  * Install it using calling the app with the parameter **-i**
  * Calling the parameter **-h** you can get help about what to do with the service in terms of execution.

