pipeline {
    agent any

    options {
        timestamps()
    }

    stages {

        stage('Checkout') {
            steps {
                echo "Checking out source code from GitHub..."
                checkout scm
            }
        }

        stage('Verify Tools') {
            steps {
                bat '''
                echo ===============================
                echo VERIFYING BUILD TOOLS
                echo ===============================

                git --version
                cmake --version
                gcc --version
                g++ --version

                echo.
                echo Git Location
                where git

                echo.
                echo GCC Location
                where gcc
                where g++

                echo.
                echo CMake Location
                where cmake
                '''
            }
        }

        stage('Debug Python') {
            steps {
                bat '''
                echo ===============================
                echo PYTHON DEBUG
                echo ===============================

                where python
                python --version

                echo.
                where pip
                pip --version

                echo.
                where conan
                conan --version

                echo.
                python -c "import sys;print(sys.executable)"
                python -c "import conan;print(conan.__file__)"
                '''
            }
        }

        stage('Conan Install') {
            steps {
                bat '''
                if exist build (
                    rmdir /s /q build
                )

                mkdir build

                cd build

                conan profile detect --force

                conan install .. ^
                    --output-folder=. ^
                    --build=missing
                '''
            }
        }

        stage('Configure') {
            steps {
                bat '''
                cd build

                cmake -G "MinGW Makefiles" ^
                    -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake ^
                    ..
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                cd build

                cmake --build .
                '''
            }
        }

        stage('Unit Tests') {
            steps {
                bat '''
                cd build

                ctest --output-on-failure
                '''
            }
        }

        stage('Run Application') {
            steps {
                bat '''
                cd build

                if exist calculator_app.exe (
                    calculator_app.exe
                ) else (
                    echo calculator_app.exe not found.
                    exit /b 1
                )
                '''
            }
        }

        stage('Package') {
            steps {
                bat '''
                if not exist artifacts (
                    mkdir artifacts
                )

                copy build\\calculator_app.exe artifacts\\
                '''
            }
        }
    }

    post {

        success {
            echo "========================================="
            echo "BUILD SUCCESSFUL"
            echo "========================================="
        }

        failure {
            echo "========================================="
            echo "BUILD FAILED"
            echo "========================================="
        }

        always {
            echo "Pipeline Finished."
        }
    }
}