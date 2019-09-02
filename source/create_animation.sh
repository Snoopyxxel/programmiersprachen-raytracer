sudo apt install ffmpeg
ffmpeg -r 24 -i /home/simon/Desktop/Raytracer-Animation/images/image_%d.ppm -vcodec png /home/simon/Desktop/Raytracer-Animation/animation_2.mp4
