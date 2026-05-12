$gpp = "C:\gcc\mingw64\bin\g++.exe"

Write-Host "Compilez generator..."
& $gpp -O2 -o generator.exe generator.cpp
if ($LASTEXITCODE -ne 0) {
    Write-Host "Eroare la compilarea generatorului!"
    exit 1
}

if (!(Test-Path "tests")) { mkdir tests | Out-Null }

$seed = 69420
$tipuri = @("random", "sortat", "sortat_invers", "few_unique", "almost_sorted", "all_equal", "neg_poz", "sawtooth")

Write-Host "Generez teste small (N=20000)..."
for ($t = 0; $t -lt $tipuri.Length; $t++) {
    .\generator.exe 20000 $seed $t > "tests\small_$($tipuri[$t]).in"
}

Write-Host "Generez teste big (N=10000000)..."
$procs = @()
for ($t = 0; $t -lt $tipuri.Length; $t++) {
    $procs += Start-Process -FilePath ".\generator.exe" `
        -ArgumentList "10000000 $seed $t" `
        -RedirectStandardOutput "tests\big_$($tipuri[$t]).in" `
        -NoNewWindow -PassThru
}
$procs | ForEach-Object { $_.WaitForExit() }

if (!(Test-Path "bin")) { mkdir bin | Out-Null }

Write-Host "Compilez algoritmi..."
$cpps = Get-ChildItem "algorithms\*.cpp"
foreach ($f in $cpps) {
    $name = $f.BaseName
    & $gpp -std=c++20 -O2 -o "bin\$name.exe" $f.FullName
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  FAIL: $($f.Name)"
    } else {
        Write-Host "  OK:   $($f.Name)"
    }
}

$exes = Get-ChildItem "bin\*.exe"
$teste = Get-ChildItem "tests\*.in"

Write-Host ""
Write-Host ("{0,-25} {1,-22} {2,10}" -f "algoritm", "test", "timp(ms)")
Write-Host ("-" * 60)

foreach ($exe in $exes) {
    $name = $exe.BaseName
    $esteN2 = ($name -like "*bubble*") -or ($name -like "*insertion*") -or ($name -like "*gnome*")

    foreach ($tin in $teste) {
        $testName = $tin.BaseName

        if ($esteN2 -and $testName -like "big_*") {
            continue
        }

        $exePath = $exe.FullName
        $testPath = $tin.FullName

        $proc = $null
        $ms = (Measure-Command {
            $proc = Start-Process -FilePath $exePath `
                -RedirectStandardInput $testPath `
                -NoNewWindow -Wait -PassThru
        }).TotalMilliseconds

        if ($proc.ExitCode -ne 0) {
            Write-Host ("{0,-25} {1,-22} {2,10}" -f $name, $testName, "FAIL")
        } else {
            Write-Host ("{0,-25} {1,-22} {2,10:F1}" -f $name, $testName, $ms)
        }
    }
}
