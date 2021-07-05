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
	end

	def add(v)
		new_e = E.new(nil,nil,v)
		if @length == 0
			@first = new_e
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

#################TEST SORTOWANIA 1###################
puts("SORTOWANIE 1")
kolekcja = Kolekcja.new()
for i in 0..10
	kolekcja.add(rand(30))
end
puts('Oto nasza kolekcja')
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
puts('Kilka przykladow dzialania funkcji okreslonych w zadaniu:')
puts('metoda swap() : swap(0,9)')
kolekcja.swap(0,10)
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
puts('metoda length oraz get(3): ')
print(kolekcja.length()," ",kolekcja.get(3))
puts()
puts('sort1 // przez wybor (wolniejsze)')
sortowanie = Sortowanie.new()
sortowanie.sort1(kolekcja)
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
puts('=============================================================')
####################TEST SORTOWANIA 2###################
puts("SORTOWANIE 2")
kolekcja = Kolekcja.new()
for i in 0..10
	kolekcja.add(rand(30))
end
puts('Oto nasza kolekcja')
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
puts('Kilka przykladow dzialania funkcji okreslonych w zadaniu:')
puts('metoda swap() : swap(2,5)')
kolekcja.swap(2,5)
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()
puts('metoda length oraz get(10): ')
print(kolekcja.length()," ",kolekcja.get(3))
puts()
puts('sort2 // babelkowe (moze byc szybsze))')
sortowanie = Sortowanie.new()
sortowanie.sort2(kolekcja)
for i in 0..10
	print(kolekcja.get(i)," ")
end
puts()