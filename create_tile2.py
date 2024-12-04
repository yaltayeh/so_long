import PIL
import PIL.Image

img = PIL.Image.open("dirt_gress_64x64.png")

_ = 64
def crop(image, x, y, w, h):
	return (image.crop((x, y, x + w, y + h)))


width, height = img.size


end_img = PIL.Image.new("RGBA", (_ * 3 * 4, _ * 6))



for i in range(2):
	edge = crop(img, _ * 3 + _ * 3 * i, 0, _ * 3, _ * 3)
	end_img.paste(edge, ((i * _ * 3), _ * 2))
	alt = crop(img,  _ * i, 0, _, _ * 3)
	for j in range(3):
		end_img.paste(crop(alt, 0, _ * j, _, _), (_ * j + (i * _ * 3), _ * 5))
	end_img.paste(crop(img, 16 * _ + _ * 2 * i, 0, _ * 2, _ * 2), (_ + (i * _ * 3), 0))
	corner = crop(img, 24 * _  + _ * 2 * i, 0, _ * 2, _ * 2)
	end_img.paste(crop(corner, 0, 0, _, _), (0+ (i * _ * 3), _ * 2))
	end_img.paste(crop(corner, _, 0, _, _), (_ * 2 + (i * _ * 3), _ * 2))
	end_img.paste(crop(corner, 0, _, _, _), (0 + (i * _ * 3), _ * 4))
	end_img.paste(crop(corner, _, _, _, _), (_ * 2 + (i * _ * 3), _ * 4))
		

end_img.save("dirt_and_gress_64x64.png")
