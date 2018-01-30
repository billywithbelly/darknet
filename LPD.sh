make
g++ `pkg-config --cflags opencv` `pkg-config --libs opencv` ImageConverter.cpp -o ImageConverter

echo please pick a picture\(the filename should not contain any spaces\):
read imagechoice 
carfound="I found a car~"
yoloresult=$(./darknet detect cfg/yolo.cfg yolo.weights $imagechoice)
echo ======================================
if [[ $yoloresult = *"I found a car~"* ]]; then
	echo "We detected a car..."
	echo "verifying for license plates..."
	plateresult=$(alpr $imagechoice)
	if [[ $plateresult = *"No license plates found."* ]];then
		echo No license plates found...
	else
		confidentPlate=$(echo $plateresult  | head -n1 | cut -d " " -f5)
		echo Found plate: $confidentPlate
		echo compressing image...
		compressionresult=$(./ImageConverter $imagechoice)
		open predictions.jpg
		open CompressedImage.jpg
	fi
else
	echo "No car found x_x"
fi
