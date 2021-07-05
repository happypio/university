class Funkcja
	@@funkcja = nil
	def put(f)
		@@funkcja = f
	end

	def get
		@@funkcja
	end

	def value(x)
		self.get().(x)
	end

	#znajodwanie miejsca zerowego na przedziale [a,b] 
	def zerowe(a,b,e) 
		fa = self.value(a)
		fb = self.value(b)
		if fa == 0
			return a
		end
		if fb == 0
			return b
		end
		if (fa * fb > 0)
			return nil
		end

		while true
			mid = (a + b) / 2
			x = self.value(mid)
			if x.abs < e
				return mid
			end
			if (fa * x) < 0
				b = mid
			else
				a = mid
				fa = x
			end
		end
	end


	def pole(a,b) #metoda trapezow
		s = 0.0
		n = 100.0
		h = ((b - a).abs )/ n # wysokosc
		f0 = self.value(a) #podstawa
		for i in 0..n
			xi = a + (i/n)*((b - a).abs)
			fi = self.value(xi) #druga podstawa
			s += (h*((fi + f0)/2)).abs
			f0 = fi
		end
		return s
	end

	def poch(x)
		dx = 0.0000000001
		return (value(x + dx) - value(x)) / dx
	end

	def rysuj(a,b)

		image = Array.new(100) {Array.new(100){'.'}}

		dx = (a.abs + b.abs)/99.0
		fb = self.value(b)
		fa = self.value(a)
		act_x = a
		for i in 0..99
			act_y = ((self.value(act_x) - fa)/(fb.abs + fa.abs))*10
			act_y = 99 - act_y.round()
			act_x += dx
			image[act_y][i] = '#'
		end
		for i in 0..99
			for j in 0..99
				print(image[i][j])
			end
		puts()
		end
	end
end

puts("Operujemy na funkcji x^3 + x - 2")
f = proc{ |x| x*x*x + x - 2}
g = Funkcja.new()
g.put(f)
puts("wartosc funkcji w x = 3")
x = g.get().(3)
puts(x)
puts("wartosc funkcji w x = -2")
x = g.value(-2)
puts(x)
puts("pochodna funkcji w x = 1")
puts(g.poch(1))
puts("pochodna funkcji w x = 5")
puts(g.poch(5))
puts("miejsce zerowe na przedziale [-2,3]")
puts(g.zerowe(-2,3,0.0000001))
puts("miejsce zerowe na przedziale [-2,0] (brak)")
puts(g.zerowe(-2,0,0.0000001))
puts("pole pod wykresem na przedziale [1,5]")
puts(g.pole(1,5))
puts("rysowanie wykresu na przedziale [-1,5] (proszę uruchomić na pełnym ekranie terminala)")
g.rysuj(-1,5)
