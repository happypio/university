template<typename FROM, typename TO>
void przenies(FROM&source, TO&destination){
	if constexpr(is_pointer<FROM>::value){
		static_assert(is_convertible<decltype(*source), TO>::value);
		destination=move(*source);
	}else{
		destination=move(source);
	}
}