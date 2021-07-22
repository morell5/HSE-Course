int main() {

    std::string s( "Long string that needs to be copied" );
    std::vector<Widget> v{};
    constexpr size_t N( 10000 );
    std::chrono::time_point<std::chrono::start = std::chrono::high_resolution_clock: : now();
    for( size_t i=0UL; i<N; ++i ) {
        Widget w{ 1, s, nullptr
        v.push_back( std: :move(w) );
    }

    end = std: :chrono::high_resolution_clock: : now();
    const std: :chrono::duration<double> elapsedTime( end - start );
    const double seconds( elapsedTime. count() );
    std::cout << " Runtime: " << seconds << "s\n\n";
}