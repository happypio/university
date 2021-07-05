class Kolekcja

	class E
		def initialize(prev,nxt,val)
			@prev = prev
			@nxt = nxt
			@val = val
		end
		def val
			return @val
		end
		def prev
			return @prev
		end
		def nxt
			return @nxt
		end
		def setp(e)
			@prev = e
		end
		def setn(e)
			@nxt = e
		end

	end

	def initialize()
		@first = nil
		@last = nil
		@length = 0
	end

	def length()
		return @length
	end

	def get(i)
		act = @first
		for j in i..@length - 2
			act = act.prev()
		end
		act.val
	end

	def set(i,v)
		act = @first
		for j in i..@length - 2
			act = act.prev()
		end
		po = act.nxt()
		przed = act.prev()
		new_e = E.new(przed,po,v)
		if po != nil
			po.setp(new_e)
		end

		if przed != nil
			przed.setn(new_e)
		end
		if i == @length - 1
			@first = new_e
		end
		if i == 0
			@last = new_e
		end
	end

	def add(v)
		new_e = E.new(nil,nil,v)
		if @length == 0
			@first = new_e
			@last = new_e
			@length += 1
		else
			tmp = @first
			@first = new_e
			new_e.setp(tmp)
			tmp.setn(new_e)
			@length += 1
		end
	end

	def swap(i, j)
		elem_i = get(i)
		elem_j = get(j)

		set(i, elem_j)
		set(j,elem_i)


	end

end

class Sortowanie
	def sort1(kolekcja) #sortowanie przez wybor
		n = kolekcja.length()
		for i in 0..n-1
			mini = 100000
			pos = 0
			for j in i..n-1
				tmp = kolekcja.get(j)
				if tmp <= mini
					mini = tmp
					pos = j
				end
			end
			kolekcja.swap(i,pos)
		end

	end
	def sort2(kolekcja) #sortowanie babelkowe
		n = kolekcja.length()
			for j in 0..n-1
				for i in 0..n-1
					if kolekcja.get(i) > kolekcja.get(i + 1)
						kolekcja.swap(i,i + 1)
					end
				end
			end
	end
end

class Wyszukiwanie
	def szukaj1(kolekcja,v) #wyszukiwanie liniowe
		n = kolekcja.length()
		for i in 0..n-1
			if kolekcja.get(i) == v
				return i
			end
		end
	end

	def szukaj2(kolekcja,v) #wyszukiwanie binsearch
		n = kolekcja.length()
		l = 0
		r = n - 1
		while l < r
			sr = (l+r)/2
			if kolekcja.get(sr) < v
				l = sr + 1
			else
				r = sr
			end
		end

		return l
	end
end

#################TEST WYSZUKIWANIA 1###################
puts("WYSZUKIWANIE 1")
kolekcja = Kolekcja.new()
for i in 0..10
	kolekcja.add(rand(30))
end
puts('Oto nasza kolekcja')
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
print('szukamy liniowo wartosci na pozycji 7 (wartosci nie sa unikalne) ',kolekcja.get(7))
wyszukiwanie = Wyszukiwanie.new()
puts()
print('Pozycja ',wyszukiwanie.szukaj1(kolekcja,kolekcja.get(7)),' wskazuje na ',kolekcja.get(7))
puts()
puts('=============================================================')
####################TEST WYSZUKIWANIE 2###################
puts("WYSZUKIWANIE 2")
kolekcja = Kolekcja.new()
for i in 0..10
	kolekcja.add(rand(30))
end
puts('Oto nasza kolekcja')
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
puts('sortujemy')
sortowanie = Sortowanie.new()
sortowanie.sort2(kolekcja)
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
print('szukamy BinSearchem wartosci na pozycji 3 (wartosci nie sa unikalne) ',kolekcja.get(3))
wyszukiwanie = Wyszukiwanie.new()
puts()
print('Pozycja ',wyszukiwanie.szukaj2(kolekcja,kolekcja.get(3)),' wskazuje na ',kolekcja.get(3))
puts()