
class Fixnum

	def factors
		result = []
		for i in 1..self
			if self%i == 0
				result << i
			end
		end
		result
	end

	def ack(y)
		if self == 0
			y + 1
		else
			if y == 0
				(self - 1).ack(1)
			else
				(self - 1).ack(self.ack(y - 1))
			end
		end
	end

	def excellent
		to_check = 0
		for i in self.factors
			to_check += i
		end
		self == to_check - self
	end

	def number_to_string
		act = self
		result = []
		while act > 0
			check = act % 10
			act = act.div(10) 
			case check
			when 0
				result.insert(0,'zero')
			when 1
				result.insert(0,'jeden')
			when 2
				result.insert(0,'dwa')
			when 3
				result.insert(0,'trzy')
			when 4
				result.insert(0,'cztery')
			when 5
				result.insert(0,'piec')
			when 6
				result.insert(0,'szesc')
			when 7
				result.insert(0,'siedem')
			when 8
				result.insert(0,'osiem')
			when 9
				result.insert(0,'dziewiec')
			end
		end
		result.join(' ')
	end
end


puts(12.factors.to_s)
puts(23.factors.to_s)
puts(16.factors.to_s)
puts(2.ack(1))
puts(2.ack(2))
puts(1.ack(1))
puts(6.excellent)
puts(12.excellent)
puts(123456789.number_to_string)