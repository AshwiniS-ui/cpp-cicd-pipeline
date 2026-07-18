pipeline {
    agent any

    options {
        timestamps()
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Verify Tools') {
            steps {
                bat '''
                echo ===== Checking Tools =====

                git --version
                cmake --version

                echo.
                echo ===== Checking GCC =====
                g++ --version

                echo.
                echo ===== GCC Location =====
                where g++

                echo.
                echo ===== CMake Location =====
                where cmake
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                if exist build (
                    rmdir /s /q build
                )

                mkdir build
                cd build

                cmake -G "MinGW Makefiles" ..

                cmake --build .
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
                    echo Executable not found.
                )
                '''
            }
        }

    }

    post {

        success {
            echo "======================================="
            echo " BUILD SUCCESSFUL "
            echo "======================================="
        }

        failure {
            echo "======================================="
            echo " BUILD FAILED "
            echo "======================================="
        }

        always {
            echo "Pipeline Finished"
        }
    }
}