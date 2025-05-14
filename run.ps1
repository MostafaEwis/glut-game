Write-Host "compiling..."
g++ ./main.cpp  -lopengl32 -lglut32win -lglu32
Write-Host "finished"
./a.exe
