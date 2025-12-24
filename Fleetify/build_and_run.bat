@echo off
echo Compiling...
g++ -std=c++17 main.cpp facade/CarRentalSystem.cpp factories/PaymentFactory.cpp factories/SearchFactory.cpp managers/CarManager.cpp managers/ReservationManager.cpp models/Car.cpp models/Customer.cpp models/Reservation.cpp strategies/AvailablitySearchStrategy.cpp strategies/NetBanking.cpp strategies/PriceSearchStrategy.cpp strategies/TypeSearchStrategy.cpp strategies/UPIPayment.cpp -o main.exe
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b %errorlevel%
)
echo Compilation successful. Running application...
echo ------------------------------------------------
main.exe
echo ------------------------------------------------
pause
