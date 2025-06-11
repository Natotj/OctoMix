board="uno"
echo "Current board: $board"

echo "(1): Compile sketch"
echo "(2): Upload sketch"
echo "(3): Compile & upload"
echo "(4): Monitor sketch"
echo "(5): Everything"
echo "(6): Change board and upload"
echo ""

read options
# compile
if [ $options -eq 1 ]; then
  arduino-cli compile -p /dev/ttyACM0

# upload
elif [ $options -eq 2 ]; then
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:$board

# compile & compile
elif [ $options -eq 3 ]; then
  arduino-cli compile -p /dev/ttyACM0
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:$board

# monitor sketch or everything (they both need the baudrate setup)
elif [ $options -eq 4 ] || [ $options -eq 5 ]; then
  echo "Baudrate: "
  echo "(1): 31250"
  echo "(2): 9600"
  echo "(3): Custom"
  echo ""
  read baudrateOptions

  # Checks if you want a 31250 or a custom baudrate
  if [ $baudrateOptions -eq 1 ]; then
    baudrate=31250
  elif [ $baudrateOptions -eq 2 ]; then
    baudrate=9600
  elif [ $baudrateOptions -eq 3 ]; then
    echo ""
    echo "Enter baudrate: "
    read baudrate
  fi

  # Commands (4 monitoring and 5 everything)
  if [ $options -eq 4 ]; then
    arduino-cli monitor -p /dev/ttyACM0 --config baudrate=$baudrate

  elif [ $options -eq 5 ]; then
    arduino-cli compile -p /dev/ttyACM0
    arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:$board
    arduino-cli monitor -p /dev/ttyACM0 --config baudrate=$baudrate
  fi

# change boardname and upload
elif [ $options -eq 6 ]; then
    echo "Enter boardname:"
    read board
    arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:$board
fi
