
class Caller {

  String id;
  String phoneNumber;
  
  Caller(String id_, String phoneNumber_) {
    id = id_;
    phoneNumber = phoneNumber_;
  }
   
  boolean isCaller(String id_) {
    return id.equals(id_);
  }      
}
