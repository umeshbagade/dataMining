import numpy as np
from PIL import Image
import cv2
import matplotlib.pyplot as plt
#from google.colab.patches import cv2_imshow

def updatecenter(centers, centerId, q):
  centers[centerId] = (centers[centerId]+q)/2.0
  return centers

# Read the grayscale image
image = Image.open('grayscale.jpg').convert('L')

# Convert the image to a NumPy array
image_array = np.array(image)

print("Enter the k value:")
k = int(input())
m, n = image_array.shape

#change later according to k
centers = []

for i in range(k):
  centers.append(i)

while True:
  prev = centers
  for p in image_array:
    for q in p:
      centerId = 0
      distance = 1000
      for idx in range(len(centers)):
        center = centers[idx]
        if(abs(q-center) < distance):
          distance = abs(q-center)
          centerId = idx
      centers = updatecenter(centers, centerId, q)
  if centers == prev:
    break;


for i in range(m):
  for j in range(n):
    centerId = 0
    distance = 1000
    for idx in range(len(centers)):
      center = centers[idx]
      if(abs(image_array[i][j]-center) < distance):
        distance = abs(image_array[i][j]-center)
        centerId = idx
    image_array[i][j] = centers[centerId]

print(image_array)
cv2.imshow("Output Image", image_array)
cv2.waitKey(0)
