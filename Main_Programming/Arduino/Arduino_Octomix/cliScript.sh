echo "(1): Compile sketch"
echo "(2): Upload sketch"
echo "(3): Monitor sketch"
echo ""

read options

if [ $options -eq 1 ]; then
  arduino-cli compile -p /dev/ttyACM0

elif [ $options -eq 2 ]; then
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno

elif [ $options -eq 3 ]; then
  arduino-cli monitor -p /dev/ttyACM0 --config baudrate=31250
fi
