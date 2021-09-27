# coding=utf-8
'''
@ Summary: resize image & save int
@ Update:  

@ file:    save_image.py
@ version: 1.0.0

@ Author:  Lebhoryi@gmail.com
@ Date:    2021/6/30 下午4:57
'''
import cv2
from pathlib import Path

IMG_SIZE = (320, 240)

def scale_image(image_path):
    img = cv2.imread(image_path)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = cv2.resize(img, IMG_SIZE)
    return img


def save_txt(image, file):
    with open(file, "w+") as f:
        print(f"#ifndef _{file.stem.upper()}_H_\n#define _{file.stem.upper()}_H_\n", file=f)
        print(f"const static uint8_t {file.stem.upper()}[] __attribute__((aligned(128))) = {'{'}", file=f)
        print(", ".join(map(lambda i: str(i), image.flatten())), file=f)
        print("};\n\n#endif", file=f)
    
    print(f"save image to {file} done.")


def main():
    image_path = "./uestc.jpg"
    image_txt = Path("./uestc.h")
    img = scale_image(image_path)
    save_txt(img, image_txt)



if __name__ == "__main__":
    main()