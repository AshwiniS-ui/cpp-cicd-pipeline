pipeline {
    agent any

    options {
        timestamps()
    }

    stages {

        stage('Checkout') {
            steps {
                echo "===== CHECKOUT SOURCE CODE ====="
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
                g++ --version

                echo.
                echo Git Location
                where git

                echo.
                echo GCC Location
                where g++

                echo.
                echo CMake Location
                where cmake
                '''
            }
        }

        stage('Clean Workspace') {
            steps {
                bat '''
                if exist build (
                    rmdir /s /q build
                )

                mkdir build
                '''
            }
        }

        stage('Configure') {
            steps {
                bat '''
                cd build

                cmake -G "MinGW Makefiles" ..
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

                if exist calculator_tests.exe (
                    calculator_tests.exe
                ) else (
                    echo No unit tests found. Skipping...
                )
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

        stage('Archive Artifacts') {
            steps {
                archiveArtifacts artifacts: 'artifacts/**', fingerprint: true
            }
        }
    }

    post {

        success {
            echo "====================================="
            echo "BUILD SUCCESSFUL"
            echo "====================================="
        }

        failure {
            echo "====================================="
            echo "BUILD FAILED"
            echo "====================================="
        }

        always {
            echo "Pipeline Finished"
        }
    }
}