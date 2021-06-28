
// find_exactly_one_checked
// 1. пройтись по набору типов
// 2. там где совпал поставить 1
// 3. пройтись по полученному набору 0 и 1
// 4. если встретили 0 => идем дальше
//    если встретили 1 и one_found = 0 => взводим флаг one_found = 1 и идем дальше
//    если встретили 1 и one_found = 1 => возвращаем флаг ambiguity = -2 (что означет найдены повторы)

// const static int not_founded = - 1;
// const static int ambiguity = not_founded - 1;

// constexpr std::size_t simplified_condition(std::size_t i, std::size_t res, bool founded_value) {
//      return (!founded_value) ? res : ((res == not_founded) ? i : ambiguity);
// }

// template<std::size_t SizeofFounded>
// constexpr std::size_t __check_dublicates__(std::size_t cur_pos, const bool (&founded)[SizeofFounded]) {
//     // условия:
//     // если мы вышли за founded => по умолчанию считаем, что не нашли 1-ц=> возвращаем not_founded (1)
//     // если в границах founded => возвращаем результат вызова из хвоста founded (2)
//     // ниже condition   (мы вышли за founded) ? (1) : (2)
//     // (2). __check_dublicates__(cur_pos + 1, founded) - идем дальше по founded в хвост
//     // перед вызовом simplified_condition мы обладаем значением __check_dublicates__(cur_pos + 1, founded) 
//     // т.е. проходим вглубь по __check_dublicates__ и возвращаем результат в  simplified_condition
//     return (cur_pos == SizeofFounded) ? not_founded :  simplified_condition(cur_pos, __check_dublicates__(cur_pos + 1, founded), founded[cur_pos]);
// }

// // в момент __check_dublicates__(cur_pos + 1, founded) возможные значения результата
// // not_founded : единицы не найдены в хвосте => т.е. хвост из 0
// // founded_exaclty_one : единица найдена в хвосте и она единаственна
// // ambiguity : в хвосте несколько единиц
// //
// // Действие на основе значения:
// // not_founded : если founded[i] == 1 => пробрасываем founded_exaclty_one
// //             : если founded[i] == 0 => пробрасываем not_founded
// // founded_exaclty_one : если founded[i] == 1 => пробрасываем ambiguity (т.к. сейчас 1 (по i позиции) и в хвосте 1-ца)
// //                     : если founded[i] == 0 => пробрасываем founded_exaclty_one (т.к. сейчас 0 (по i позиции) и в хвосте 1-ца)
// // ambiguity: продолжаем пробрасывать 1

// // Заметим, что при условии founded[i] == 0 пробрасывается возвращаемое значение
// // not_founded -> not_founded
// // founded_exaclty_one -> founded_exaclty_one
// // ambiguity -> ambiguity
// // тогда пишем
// // (!founded[i]) ? tail_has_ones : <тут остальные проверки>
// // 
// // Заметим, что founded[i] == 1 пробрасывается:
// // not_founded -> founded_exaclty_one
// // founded_exaclty_one -> ambiguity
// // ambiguity -> ambiguity 
// // тогда смотрим если пришел not_founded, то пробрасываем founded_exaclty_one, иначе пробрасывается ambiguity
// //
// // итог: (!founded[i]) ? tail_has_ones : (tail_has_ones == not_founded) ? founded_exaclty_one : ambiguity
// // получаем
// //  
// // (!founded[i]) ? __check_dublicates__(cur_pos + 1, founded) : (__check_dublicates__(cur_pos + 1, founded) == not_founded) ? founded_exaclty_one : ambiguity
// //  
// // но читать такое сложно!!
// // давайте данынй condition вынесем в отдельную функцию, а значения __check_dublicates__(cur_pos + 1, founded) будем туда передавать
// // 
// // simplified_condition
// // std::size_t simplified_condition(std::size_t i, std::size_t res, bool founded_val) {
// //    return (!founded_val) ? res : (res == not_founded) ? founded_exaclty_one : ambiguity;
// // }
// // вот founded_exaclty_one мы отдельно явно заводить не будем, под founded_exaclty_one мы продолжим пробрасывать текущий индекс понимая, что 
// // семантически это founded_exaclty_one
// //
// // приходим к 
// //
// // std::size_t simplified_condition(std::size_t i, std::size_t res, bool founded_val) {
// //    return (!founded_val) ? res : (res == not_founded) ? i : ambiguity;
// // }

// template<typename TargetType, typename... Types>
// struct _find_exactly_one_checked_ {
//     // 1. пройтись по набору типов
//     // 2. там где совпал поставить 1
//     constexpr static bool founded[sizeof...(Types)] = {std::is_same<TargetType, Types>::value...}; 
//     // 3. пройтись по полученному набору 0 и 1
//     constexpr static std::size_t value = __check_dublicates__(0, founded);
//     static_assert(value != not_founded, "type not found in type list" );
//     static_assert(value != ambiguity, "type occurs more than once in type list");
// };

// template<typename T>
// struct _find_exactly_one_checked_<T> {
//     static_assert(!std::is_same<T, T>::value, "type not in empty type list");
// };

// template<typename TargetType, typename... Types>
// struct _find_exactly_one_t : public _find_exactly_one_checked_<TargetType, Types...> {

// };


int main() {
    return 0;
}