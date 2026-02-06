class Name implements Comparable<Name> {
private String name;
private String firstSurname;
private String secondSurname;
public Name(String name, String firstSurname, String secondSurname) {
this.name = name;
this.firstSurname = firstSurname;
this.secondSurname = secondSurname;
}
public String getName() {
return this.name;
}
public void setName(String name) {
this.name = name;
}
public String getFirstSurname() {
return this.firstSurname;
}
public void setFirstsurame(String firstSurname) {
this.firstSurname = firstSurname;
}
public String getSecondSurname() {
return this.secondSurname;
}
public void setSecondSurname(String secondSurname) {
this.secondSurname = secondSurname;
}
public String toString() {
return this.firstSurname+" "+this.secondSurname+", "+this.name;
}
@Override
public int compareTo(Name name){
	int result=0;
	try {
		Name aux=(Name)  name;
		if(this.firstSurname.compareTo(aux.getFirstSurname())<0){
			result=-1;
		}else if(this.firstSurname.compareTo(aux.getFirstSurname())>0) {
			result=1;
		}else if(this.secondSurname.compareTo(aux.getSecondSurname())<0) {
			result=-1;
		}else if(this.secondSurname.compareTo(aux.getSecondSurname())>0) {
			result=1;
		}else if(this.name.compareTo(aux.getName())<0) {
			result=-1;
		}else if(this.name.compareTo(aux.getName())>0) {
			result=1;
		}		
	}catch(ClassCastException e) {
		System.err.println("caca");
		System.exit(1);
	}
	return result;
}
}
