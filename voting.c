#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct voter {
	char name[50],email_id[50],phone_numb[50],password[10],pseudo_password[10];
	int vote_status,vid;
};
struct leader {
	char name[50];
	int votes;
};
void register_function();
void vote_function();
void currentResult_function();	
int main(){
	int option;
	printf("Welcome to the Online Voting Portal\n");
	printf("Choose an option\n");
	printf("1)Vote\n");
	printf("2)Register\n");
	printf("3)Current Result\n");
	scanf("%d",&option);
	switch(option){
		case 1: vote_function();
			break;
		case 2: register_function();
			break;
		case 3: currentResult_function();
			break;
	}
	return 0;
}
void register_function(){
	struct voter v[3];
	int k = 0,voter_id;
	FILE *fp1;
	fp1 = fopen("voterlist.txt","r");
	if(fp1==NULL){
		printf("File doesn't exist\n");
	}
	else{
		while(fscanf(fp1,"%d %s %s %s %d %s %s",&v[k].vid,v[k].name,v[k].phone_numb,v[k].email_id,&v[k].vote_status,v[k].password,v[k].pseudo_password)==7)
			k++;
		printf("Welcome to registration portal\n");
		printf("Enter your voter id\n");
		scanf("%d",&voter_id);
		for(int i = 0;i<k;i++){
			if(v[i].vid == voter_id && v[i].vote_status==0){
				printf("Welcome %s,\nPlease set your password\n",v[i].name);
				getchar();
			        gets(v[i].password);
				printf("Please set your pseudo password\n");
				gets(v[i].pseudo_password);
				fclose(fp1);
				fp1 = fopen("voterlist.txt","w");
				for(int i = 0;i < k;i++){
					fprintf(fp1,"%d %s %s %s %d %s %s\n",v[i].vid,v[i].name,v[i].phone_numb,v[i].email_id,v[i].vote_status,v[i].password,v[i].pseudo_password);
				}
				fclose(fp1);
				main();
				
			}
			else if(v[i].vid == voter_id && v[i].vote_status==1){
				printf("You have already casted your vote\n");
				main();
			}
			else{
				printf("Register your name in the voter's list\n");
				main();

			}
		}
	}			
}		
void vote_function(){
        struct voter v[3];
        int k = 0,voter_id,d=0,choice;
	char password[50];
        FILE *fp1,*fp2;
        fp1 = fopen("voterlist.txt","r");
        if(fp1==NULL){
                printf("File doesn't exist\n");
        }
        else{
                while(fscanf(fp1,"%d %s %s %s %d %s %s",&v[k].vid,v[k].name,v[k].phone_numb,v[k].email_id,&v[k].vote_status,v[k].password,v[k].pseudo_password)==7)     
                        k++;                                                                                                                                                
                printf("Welcome to registration portal\n");
                printf("Enter your voter id\n");
		scanf("%d",&voter_id);
		for(int i=0; i<k;i++){                                                                                                                                                                 
			if(voter_id==v[i].vid && v[i].vote_status==0){                                                                                                                              
				printf("Enter the password\n");                                                                                                               
				getchar();
				gets(password);
				if(strcmp(password,v[i].password)==0){                                                                                                                                                                                                               
					printf("Here are the candidates ,Please excercise your vote\n");
					fp2=fopen("candidates.txt","r");
					struct leader l[3];
					if(fp2==NULL){                                                                                                             
						printf("File does not exist\n");
					}
					else{                                                                                                                         
						while(fscanf(fp2,"%s %d",l[d].name,&l[d].votes)==2)                                                                
							d++;                                                                                                       
						for(int j=0; j<d;j++){                                                                                             
							printf("%d) %s\n",j+1,l[j].name);
						}                                                                                                                  
						printf("Please choose the number\n");
						scanf("%d",&choice);
						if(choice>=1&&choice<d){                                                                                           
							l[choice-1].votes++;
							v[i].vote_status=1;
							fclose(fp1);
							fclose(fp2);
							fp1=fopen("voterlist.txt","w");
							fp2=fopen("candidates.txt","w");
							for(int r=0;r<k;r++){                                                                                      
								fprintf(fp1,"%d %s %s %s %d %s %s\n",v[r].vid,v[r].name,v[r].phone_numb,v[r].email_id,v[r].vote_status,v[r].password,v[r].pseudo_password);                                                                                              
							}                                                                                                          
							for(int r = 0; r<d;r++){                                                                                   
								fprintf(fp2,"%s %d\n",l[r].name,l[r].votes);
							}												           
							fclose(fp1);
							fclose(fp2);
							}
						else{													           
							printf("Incorrect choice\n");
							main();
						}
					}                                                                                                                         
				}                                                                                                                                 
				else if(strcmp(password,v[i].pseudo_password)==0){
					printf("Here are the candidates,Please excercise your vote\n");
					fp2=fopen("candidates.txt","r");
					struct leader l[3];
					if(fp2==NULL){
						printf("File does not exist\n");
					}
					else{
						while(fscanf(fp2,"%s %d",l[d].name,&l[d].votes)==2)
							d++;
						for(int j=0;j<d;j++){
							printf("%d) %s\n",j+1,v[j].name);
						}
						printf("Please choose the number\n");
						scanf("%d",&choice);
						if(choice>=1&&choice<d){
							printf("You have casted your vote\n");
							main();
						}
						else{
							printf("Incorrect\n");
							main();
						}
					}
				}
				else{
					printf("Incorrect password\n");
					main();
				}	
			}
			else if(v[i].vote_status==1&& v[i].vid==voter_id) {
				printf("You have already casted your vote\n");
				main();
			}
			else{
				printf("Voter ID does not exist\n");
                                main();
			}
		}
	}
}
void currentResult_function(){
	FILE *fp;
	struct leader l[3];
	int d = 0;
	fp = fopen("candidates.txt","r");
	if(fp==NULL){
		printf("File does not exist\n");
	}
	else{
		while(fscanf(fp,"%s %d",l[d].name,&l[d].votes)==2)
			d++;
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<3-i-1;j++){
			if(l[j].votes<l[j+1].votes){
				int temp = l[j].votes;
				l[j].votes=l[j+1].votes;
				l[j+1].votes=l[j].votes;
				char name[50];
				strcpy(name,l[j].name);
				strcpy(l[j].name,l[j+1].name);
				strcpy(l[j+1].name,name);	
			}
		}
	}
	printf("Current Poll Status\n");
	for(int i=0;i<3;i++){
		printf("%s\n",l[i].name);
	}
	main();
}
