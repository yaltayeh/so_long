import PIL
import PIL.Image

fonts = []

fonts.append(PIL.Image.open("Wooden_font/RedWood.png"))
fonts.append(PIL.Image.open("Wooden_font/Wood.png"))
fonts.append(PIL.Image.open("Wooden_font/WhiteWood.png"))
img2 = PIL.Image.open("Wooden_font/banners.png")

_ = 15
__ = 32
def crop(image, x, y, w, h):
	return (image.crop((x, y, x + w, y + h)))

res_img = PIL.Image.new("RGBA", (_*11 + __*8, __*3))

# for i, img in enumerate(fonts):
# 	for l in range(6):
# 		letter = crop(img, 0, 25 * l, _* 12, 25)
# 		res_img.paste(letter, [_*12 * l, 2 + i * 32])

for i, img in enumerate(fonts):
	x = 4
	zero = crop(img, _*11, 25 * 2, 15, 25)
	res_img.paste(zero, [0, x + i * 32])

	letter = crop(img, _*2, 25 * 2, _*9, 25)
	res_img.paste(letter, [15, x + i * 32])

	colon = crop(img, _*2, 25 * 5, 15, 25)
	res_img.paste(colon, [_*10, x + i * 32])

	banner = crop(img2, __*3 + __*9 * i, __*33, __, __)	
	res_img.paste(banner, [_*11, 32 * i])

	banner = crop(img2, __*4 + __*9 * i, __*33, __*3, __)	
	res_img.paste(banner, [_*11 + __, 32 * i])
	
	banner = crop(img2, __*3 + __*9 * i, __*34, __, __)	
	res_img.paste(banner, [_*11 + __*4, 32 * i])

	banner = crop(img2, __*4 + __*9 * i, __*34, __*3, __)	
	res_img.paste(banner, [_*11 + __*5, 32 * i])




res_img.save("textures/banner.png")


