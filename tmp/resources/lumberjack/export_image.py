import PIL
import PIL.Image

_ = 64

def crop(img, x, y, w, h):
	return (img.crop((x, y, x + w, y + h)))

imgs = []

imgs.append(PIL.Image.open("no_logs.png"))
imgs.append(PIL.Image.open("3_logs.png"))
imgs.append(PIL.Image.open("9_logs.png"))

res = PIL.Image.new("RGBA", (_ * 12, _ * 20 * 3))

y_offset = 0
for img in imgs:
	__, height = img.size
	res.paste(crop(img, 0, 0, _ * 12, _ * 12), 			(0, y_offset))
	res.paste(crop(img, 0, height - _ * 8, _ * 12, _ * 8), (0,y_offset + _ * 12))
	y_offset += _ * 20


res.save("lumberjack.png")