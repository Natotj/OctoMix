echo "(1): Compile sketch"
echo "(2): Upload sketch"
echo "(3): Monitor sketch"
echo "(4): Everything"
echo ""

read options
# compile
if [ $options -eq 1 ]; then
  arduino-cli compile -p /dev/ttyACM0

# upload 
elif [ $options -eq 2 ]; then
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno

# monitor sketch or everything (they both need the baudrate setup)
elif [ $options -eq 3 ] || [ $options -eq 4 ]; then
  echo "Baudrate: "
  echo "(1): 31250"
  echo "(2): Custom"
  echo ""
  read baudrateOptions

  # Checks if you want a 31250 or a custom baudrate 
  if [ $baudrateOptions -eq 1 ]; then
    baudrate=31250
  elif [ $baudrateOptions -eq 2 ]; then
    echo ""
    echo "Enter baudrate: "
    read baudrate
  fi

  # Commands (3 monitoring and 4 everything) 
  if [ $options -eq 3 ]; then
    arduino-cli monitor -p /dev/ttyACM0 --config baudrate=31250
   
  elif [ $options -eq 4 ]; then
    arduino-cli compile -p /dev/ttyACM0
    arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno
    arduino-cli monitor -p /dev/ttyACM0 --config baudrate=$baudrate
  fi
fi
