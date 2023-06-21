# Command_Line_Arguments
Chương trình sử dụng Jenkins Pipeline để build
# Tạo file "Dockerfile"
file Dockerfile có nội dung như sau:
***************************************************************************
FROM jenkins/jenkins:lts-jdk11
# if we want to install via apt
USER root
RUN apt-get update && apt-get install -y build-essential
# drop back to the regular jenkins user - good practice
USER jenkins
***************************************************************************
Build Doceker image
docker build -t jenkins/jenkins:lts-jdk11 -f Dockerfile .
run
docker run -p 8080:8080 -p 50000:50000 --restart=on-failure -v jenkins_home:/var/jenkins_home jenkins/jenkins:lts-jdk11

++++++++++++++++ STEP 2 ++++++++++++++++
Đặng nhập vào Jenkins servers localhost:8080
 tạo Jenkinsfile
 
***************************************************************************
 pipeline {
    agent any
    
    stages {
        stage("Clean Up"){
            steps {
                deleteDir()
            }
        }
        stage('Checkout') {
            steps {
                // Đặt đường dẫn của mã nguồn chương trình C
                sh "git clone https://github.com/cuongmaidt2/Command_Line_Arguments.git"
            }
        }
        
        stage('Build') {
            steps {
                // Thực hiện các lệnh build chương trình C
                sh "gcc -o /var/jenkins_home/workspace/Command_Line_Arguments/Command_Line_Arguments/Command_Line_Arguments /var/jenkins_home/workspace/Command_Line_Arguments/Command_Line_Arguments/Command_Line_Arguments.c"
            }
        }
        
        stage('Test') {
            steps {
                // Thực hiện các lệnh kiểm tra chương trình C
                sh '''
                cd /var/jenkins_home/workspace/Command_Line_Arguments/Command_Line_Arguments
                ./Command_Line_Arguments Argv1 Argv2
                '''
            }
        }
    }
}

***************************************************************************

