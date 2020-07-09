
type field_types =
  | String
  | Integer
  | Boolean
  | Map
  | Array
  | BinaryId
  | DateTime
  | Date
  | Time;

type field = {
  name: string,
  field_type: field_types,
  opts: list(option(string))
}

type timestamp_opts = {
  mutable inserted_at: field,
  mutable updated_at: field,
};

type schema = {
  primary_key: string,
  table_name: string,
  fields: list(field),
  timestamps: timestamp_opts
}

let get_table_name = (schema: schema) => {
  schema.table_name;
};

let get_default_timestamp = (name: string) =>
  {name: name, field_type: DateTime, opts: []};

let timestamps = (~inserted_at: option(field)=?, ~updated_at: option(field)=?, schema: schema): schema => {
  let opts: timestamp_opts = {
    inserted_at: get_default_timestamp("inserted_at"),
    updated_at: get_default_timestamp("updated_at")
  };

  // let x =
  //   switch (inserted_at) {
  //   | Some(inserted_at) => inserted_at
  //   | None => get_default_timestamp("inserted_at")
  //   };

  {...schema, timestamps: opts}
};

timestamps(
  ~inserted_at = {name: "created_at", field_type: DateTime, opts: []},
  ~updated_at = {name: "updated_at", field_type: DateTime, opts: []}
);

// module Factory = {
//   let new_schema = (table_name: string, fields: block): schema => {
//     let (schema_fields, timestamps) = do_smth(fields);
    
//     let timestamps = {
//       inserted_at: get_default_timestamp("inserted_at"),
//       updated_at: get_default_timestamp("updated_at")
//     };

//     {
//       primary_key: "id",
//       table_name: table_name,
//       fields: schema_fields,
//       timestamps: timestamps
//     };
//   }
// }

// let add_field = (field_name: string, field_type: field_types, ~null=false, ~default=None) => {
//   let has_default =
//     switch default {
//     | None => false
//     | Some(_) => true
//     };

//   // if (has_default) {

//   // }
// }

// Factory.new_schema("users", () => {
//   add_field("name", String, ~default = "aleDsz");
//   add_field("age", Integer);
//   add_field("birthdate", Date, ~null = false);

//   timestamps;
// })