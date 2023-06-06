import cv2
import numpy as np

def hough(img):
    (h, w)= img.shape
    centro = (h/2, w/2)
    
    # m = -1 / tg(teta)  
    # c = r / sin(teta)
    # r = x cos  + y sin
    
    # vamos pegar teta variando de 0 a 180 graus
    # ro variando de -d ate d onde d -e sqrt(h^2 + w^2)
    # arr = np.zeros((2d, 180))
    # verificar somente os pixeis nas bordas
    # percorrer 180 e computar oro equivalente a esse teta
    ro = 0;
    d = int(np.sqrt(h**2 + w**2))
    arr = np.zeros((2*d, 180))
    for x in range(h):
        for y in range(w):
            print(img[x,y])
            for ro in range(180):
                pass
    
    
img = cv2.imread("./palitos.png");
imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
sobelxy = cv2.Sobel(src=imgGray, ddepth=cv2.CV_64F, dx=1, dy=1, ksize=5)
hough(sobelxy)
#cv2.imshow("o", img)
#cv2.imshow("o2", imgGray)
#cv2.imshow("o3", sobelxy)


cv2.waitKey(0)
cv2.destroyAllWindows()
