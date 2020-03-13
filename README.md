# WorWorld

# Compileren van project
Navigeer naar directory waar RobotArm opgeslagen is in een terminal
Voer caktin_make uit
Voer source devel/setup.bash uit

# runnen van applicatie
Open een terminal en voer hier roscore uit
Open nog twee terminals op de locatie van RobotArm
In een van de twee terminals moet rosrun driver Driver uitgevoerd worden
In de andere terminal moet rosrun motion_planner MotionPlanner
Als het goed is is werkt de applicatie nu en staat de robot in de park
Als er een foutmelding is met betrekking tot de port, kan het zijn dat deze in de code verkeerd staat. Ga naar driver/src/MessageSender.cpp. Wijzig in deze file op regel 6 de /dev/ttyUSB0 naar de juiste port.
